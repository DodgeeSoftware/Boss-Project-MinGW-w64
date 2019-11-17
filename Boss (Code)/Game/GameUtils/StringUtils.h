#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <wctype.h>

namespace Utils
{
    //! Split strings according to a delimiter
    inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }
    //! Split strings according to a delimiter
    inline std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }
    //! Remove whitespace
    inline std::string removeWhiteSpace(std::string text)
    {
        //text.erase(std::remove_if(text.begin(), text.end(), std::isspace), text.end());
        text.erase(std::remove_if(text.begin(), text.end(),isspace),text.end());
        return text;
    }
    //! Convert a string to upper case
    inline std::string toUpper(std::string text)
    {
        if (text.size() == 0)
            return text;
        std::string uppercase(text);
        for (std::string::iterator p = uppercase.begin(); p != uppercase.end(); p++)
            *p = std::toupper(*p);
        return uppercase;
    }
    //! Convert a string to lower case
    inline std::string toLower(std::string text)
    {
        if (text.size() == 0)
            return text;
        std::string lowercase(text);
        for (std::string::iterator p = lowercase.begin(); p != lowercase.end(); p++)
            *p = std::tolower(*p);
        return lowercase;
    }
    //! Convert bool data type into a c++ style string
    inline std::string toString(bool value)
    {
        if (value == true)
            return std::string("TRUE");
        return std::string("FALSE");
    }
    //! Convert string data type into a bool
    inline bool toBool(std::string value)
    {
        // Convert value to upper case
        for (std::string::iterator p = value.begin(); p != value.end(); p++)
            *p = std::toupper(*p);
        // If value is "TRUE" return true
        if (value == "TRUE")
            return true;
        // False is default return value
        return false;
    }
    //! Convert long data type into c++ style strings
    inline std::string toString(long value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to a long data type
    inline long toLong(std::string value)
    {
        return atol(value.c_str());
    }
    //! Convert an unsigned int data type into c++ style string
    inline std::string toString(unsigned int value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to an unsigned int data type
    inline unsigned int toUnsignedInt(std::string value)
    {
        // NOTE: May have undesirable effects (there is no native c function to do this)
        return atol(value.c_str());
    }
    //! Convert an int data type into c++ style string
    inline std::string toString(int value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to an int data type
    inline int toInt(std::string value)
    {
        return atoi(value.c_str());
    }
    //! Convert a float data type into c++ style string
    inline std::string toString(float value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to a float data type
    inline float toFloat(std::string value)
    {
        return atof(value.c_str());
    }
    //! Convert a double data type into c++ style string
    inline std::string toString(double value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to a double data type
    inline double toDouble(std::string value)
    {
        return atof(value.c_str());
    }
    //! Convert a short int data type into c++ style string
    inline std::string toString(short int value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to an short int data type
    inline short int toShortInt(std::string value)
    {
        // NOTE: May have undesirable effects (there is no native c function to do this)
        return atol(value.c_str());
    }
    //! Convert unsigned long data type into c++ style strings
    inline std::string toString(unsigned long value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to a unsigned long data type
    inline unsigned long toUnsignedLong(std::string value)
    {
        // NOTE: May have undesirable effects (there is no native c function to do this)
        return atol(value.c_str());
    }
    //! Convert long long data type into c++ style strings
    inline std::string toString(long long value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to a long long data type
    inline long long toLongLong(std::string value)
    {
        // NOTE: May have undesirable effects (there is no native c function to do this)
        return atol(value.c_str());
    }
    //! Convert unsigned long long data type into c++ style strings
    inline std::string toString(unsigned long long value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert c++ style string to a unsigned long long data type
    inline unsigned long long toUnsignedLongLong(std::string value)
    {
        // NOTE: May have undesirable effects (there is no native c function to do this)
        return atol(value.c_str());
    }
    //! Convert a char data type into c++ style string
    inline std::string toString(char value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert a unsigned char data type into c++ style string
    inline std::string toString(unsigned char value)
    {
        std::ostringstream buffer;
        buffer << value;
        return std::string(buffer.str());
    }
    //! Convert a c-style string to a long data type
    inline long toLong(const char* text)
    {
        return atol(text);
    }
    //! Convert a c-style string to an int data type
    inline int toInt(const char* text)
    {
        return atoi(text);
    }
    //! Convert a c-style string to a float data type
    inline float toFloat(const char* text)
    {
        return atof(text);
    }
    //! Convert a c-style string to a float data type
    inline bool toBool(const char* text)
    {
        std::string lowercase(text);
        for (std::string::iterator p = lowercase.begin(); p != lowercase.end(); p++)
            *p = std::tolower(*p);
        if (lowercase == "true")
            return true;
        else
            return false;
    }
}

#endif // STRINGUTILS_H
