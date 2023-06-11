## 参考

[C++文件读写详解（ofstream,ifstream,fstream）](https://blog.csdn.net/kingstar158/article/details/6859379)
[c++输入文件流ifstream用法详解](https://blog.csdn.net/sinat_36219858/article/details/80369255)

|模式|含义|
|--|--|
|ios::in|       为输入(读)而打开文件|
|ios::out|      为输出(写)而打开文件|
|ios::ate|      初始位置：文件尾|
|ios::app|      所有输出附加在文件末尾|
|ios::trunc|    如果文件已存在则先删除该文件|
|ios::binary|   二进制方式|

### 文本文件读写
```c++ linenums="1"
#include <iostream>
#include <fstream>
#include <vector>

/**
 * @brief 逐行读取文本文件
 *
 * @param filename 文件名
 * @return std::vector<std::string> 文件内容保存到 vector
 */
static std::vector<std::string> readTxtFile(std::string filename) {
    std::vector<std::string> content;
    std::string line;

    std::ifstream file;
    file.open(filename, std::ios::in);
    if (!file)
    {
        std::cout << "文件打开失败" << std::endl;
        return content;
    }

    while (!file.eof())
    {
        std::getline(file, line);
        content.push_back(line);
    }

    file.close();

    return content;
}

/**
 * @brief 写入文本文件
 *
 * @param filename 文件名
 * @param content 文件内容
 */
static void writeTxtFile(std::string filename, std::vector<std::string> content) {
    std::ofstream out;
    out.open(filename, std::ios::out);
    if (!out.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return ;
    }

    if (content.size() <= 0) {
        return ;
    }

    for (auto line : content)
    {
        out << line << std::endl;
    }
    out.close();
}

int main() {

    auto content = readTxtFile("./main.cpp");
    for (auto line : content)
    {
        std::cout << line << std::endl;
    }

    writeTxtFile("test.txt", content);

    std::cout << std::endl << "Hello World!" << std::endl;
    return 0;
}
```