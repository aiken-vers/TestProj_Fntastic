#include <iostream>
#include <algorithm>
#include <string>
#include <map>



int main()
{ 
    std::string entry;
    std::string line;
    std::map<char, uint16_t> letters;
    static char duplicate = ')';
    static char unique = '(';

    std::cout << "Enter the string to convert. Type \"exit\" to quit." << std::endl;
    do     
    {
        std::getline(std::cin, line);
        entry = line;
        std::transform(entry.begin(), entry.end(), entry.begin(), ::tolower);

        for (char c : entry)
        {
            ++letters[c];
        }

        for (int i = 0; i < entry.length(); ++i)
        {
            entry[i] = (letters[entry[i]] > 1) ? duplicate : unique;
        }
        std::cout << entry << std::endl;

        letters.clear();
    }     
    while (line != "exit");

    return 0;
}
