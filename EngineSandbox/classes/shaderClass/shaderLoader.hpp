#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

class ShaderLoader{
public:
    ShaderLoader() = delete;
    ShaderLoader(std::string path) : _path(path){
        data.open(path);
        if (!data.is_open()) std::cout << "invalid path: " << path;
        std::string line;
        ShaderType type = ShaderType::NONE;
        while (getline(data, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos) type = ShaderType::FRAGMENT;
            }
            else shaderSource[(int)type] << line << '\n';
            if (line.empty() || line.find_first_not_of("\r\n\t ") == std::string::npos) continue;
        }
        vertexSource = shaderSource[0].str();
        fragmentSource = shaderSource[1].str();
    }

    const char* const* GetFragmentShaderSource() {
        F_ptr = fragmentSource.c_str();
        return &F_ptr;
    };

    const char* const* GetVertexShaderSource() {
        V_ptr = vertexSource.c_str();
        return &V_ptr;
    };

private:
    enum ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    const char* V_ptr = nullptr;
    const char* F_ptr = nullptr;
    std::string vertexSource;
    std::string fragmentSource;
    std::string _path; 
    std::ifstream data;
    std::stringstream shaderSource[2];
};

 