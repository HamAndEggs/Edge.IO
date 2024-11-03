
#include "Application.h"
#include "ResourceMap.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

class MyUI : public eui::Application
{
public:
    MyUI(const std::string& path):mPath(path){}
    virtual ~MyUI(){};

    virtual void OnOpen(eui::Graphics* pGraphics)
    {
        std::cout << "******* Loading application\n";
        const std::string jsonString = LoadFileIntoString("./example.json");
        const tinyjson::JsonProcessor Json(jsonString,true);

        mResources = new eui::ResouceMap(Json.GetRoot(),pGraphics);
        mRoot = new eui::Element(Json.GetRoot(),mResources);
    };

    virtual void OnClose()
    {

    }

    virtual void OnUpdate(){}

    virtual eui::ElementPtr GetRootElement(){return mRoot;}
    virtual uint32_t GetUpdateInterval()const{return 1000 / 60;}

    virtual int GetEmulatedWidth()const{return 720;}
    virtual int GetEmulatedHeight()const{return 720;}


private:
    const std::string mPath;
    eui::ElementPtr mRoot = nullptr;
    eui::ResouceMapPtr mResources;


    std::string LoadFileIntoString(const std::string& pFilename)
    {
        std::ifstream jsonFile(pFilename);
        if( jsonFile.is_open() )
        {
            std::stringstream jsonStream;
            jsonStream << jsonFile.rdbuf();// Read the whole file in...

            return jsonStream.str();
        }

        std::throw_with_nested(std::runtime_error("Jons file not found " + pFilename));

        return "";
    }
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
