
#include "Application.h"

#include <filesystem>

class MyUI : public eui::Application
{
public:
    MyUI(const std::string& path):mPath(path){}
    virtual ~MyUI(){};

    virtual void OnOpen(eui::Graphics* pGraphics)
    {
        mLoading = new eui::Element;
        mLoading->SetID("Loading screen");
        mLoading->SetText("Loading");
        mLoading->GetStyle().mBackground = eui::COLOUR_BLUE;

        int normalFont = pGraphics->FontLoad(mPath + "liberation_serif_font/LiberationSerif-Regular.ttf",40);
        mLoading->SetFont(normalFont);

        mRoot = mLoading;
    };

    virtual void OnClose()
    {
        delete mLoading;
    }

    virtual void OnUpdate(){}

    virtual eui::ElementPtr GetRootElement(){return mRoot;}
    virtual uint32_t GetUpdateInterval()const{return 1000 / 60;}

    virtual int GetEmulatedWidth()const{return 720;}
    virtual int GetEmulatedHeight()const{return 720;}


private:
    const std::string mPath;
    eui::ElementPtr mLoading = nullptr;
    eui::ElementPtr mRoot = nullptr;
};


int main(const int argc,const char *argv[])
{
#ifdef NDEBUG
    std::cout << "Release\n";
#else
    std::cout << "Debug\n";
#endif


// Crude argument list handling.
    std::string path = "./";
    if( argc == 2 && std::filesystem::directory_entry(argv[1]).exists() )
    {
        path = argv[1];
        if( path.back() != '/' )
            path += '/';
    }

    MyUI* theUI = new MyUI(path); // MyUI is your derived application class.
    eui::Application::MainLoop(theUI);
    delete theUI;

    return EXIT_SUCCESS;
}
