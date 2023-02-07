#include <fmt/core.h>
#include <sigslot/signal.hpp>
#include <array>

class Model;

struct Ui
{
    class BoardView
    {
    public:
        explicit BoardView(const Model& model) : model{model} {}

        void renderData()
        {
            //TODO: render only data that has changed since last render
            fmt::print("Ui::BoardView::renderData\n");
        }

    private:
        const Model& model;
    };

    class User
    {
    public:
        sigslot::signal<> setCodebrakerCode;
        sigslot::signal<> setCodemakerCode;
    };

    BoardView boardView;
    User user;
};

struct Model
{
    using Code = std::array<int, 4>;
    using Key = std::array<int, 4>;

    void newCodemakerCode()
    {
        fmt::print("Model::newCodemakerCode\n");
        //codebrakerPatterns.push_back({});
        dataChanged();
    }

    void newCodebrakerCode()
    {
        fmt::print("Model::newCodebrakerCode\n");
        codebrakerCodes.push_back({});
        dataChanged();
    }

    void newCodebrakerKey()
    {
        fmt::print("Model::newCodebrakerKey\n");
        //codebrakerPatterns.push_back({});
        dataChanged();
    }

    sigslot::signal<> dataChanged;

    std::vector<Code> codebrakerCodes{};
    std::vector<Key> codebrakerKeys{};
    Key codemakerKey{};
};

class Controller
{
public:
    explicit Controller(Model& model) : model{model} {}

    void newCodemakerCode()
    {
        model.newCodemakerCode();
    }

    void newCodebrakerCode()
    {
        model.newCodebrakerCode();
        checkPatterns();
    }

    void newCodebrakerKey()
    {
        model.newCodebrakerKey();
    }

    sigslot::signal<> checkPatterns;

private:
    Model& model;
};

struct Logic
{
    //void comparePatterns(GameModel::CodebrakerPattern codebrakerPattern, GameModel::CodemakerPattern codemakerPattern)
    void comparePatterns()
    {
        fmt::print("Logic::comparePatterns\n");
        setCodebrakerKey();
    }

    sigslot::signal<> setCodebrakerKey;
};


int main()
{
    Model model{};
    Controller controller{model};
    Ui ui{
        .boardView = Ui::BoardView{model},
        .user = Ui::User{}
    };
    Logic logic{};

    ui.user.setCodemakerCode.connect(&Controller::newCodemakerCode, &controller);
    ui.user.setCodebrakerCode.connect(&Controller::newCodebrakerCode, &controller);
    model.dataChanged.connect(&Ui::BoardView::renderData, &ui.boardView);
    controller.checkPatterns.connect(&Logic::comparePatterns, &logic);
    logic.setCodebrakerKey.connect(&Controller::newCodebrakerKey, &controller);

    ui.user.setCodemakerCode();
    ui.user.setCodebrakerCode();

    return 0;
}
