#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// C/C++ Includes
#include <string>

// Lua
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

// LuaBridge
#include <LuaBridge/LuaBridge.h>

class GameObject
{
    // ***************
    // * CONSTRUCTOR *
    // ***************

    public:
        //! Constructor
        GameObject();
        //! Destructor
        virtual ~GameObject ();

    protected:
        // Methods and members

    // *************
    // * OPERATORS *
    // *************

    public:
        // Methods and members

    protected:
        // Methods and members

    // *************************
    // * GAME OBJECT FUNCTIONS *
    // *************************

    public:
        //! Think
        virtual void think();
        //! Update
        virtual void update();
        //! Draw
        virtual void draw();
        //! Clear
        virtual void clear();
        //! Free
        virtual void free();

    protected:
        // Members and methods

    // *************
    // * TRANSFORM *
    // *************

    public:
        //! Get x
        virtual float getX() { return x; }
        //! Set x
        virtual void setX(float x) { this->x = x; }
        //! Get y
        virtual float getY() { return y; }
        //! Set y
        virtual void setY(float y) { this->y = y; }
        //! Get x velocity
        virtual float getXVelocity() { return xVelocity; }
        //! Set x velocity
        virtual void setXVelocity(float xVelocity) { this->xVelocity = xVelocity; }
        //! Get y velocity
        virtual float getYVelocity() { return yVelocity; }
        //! Set y velocity
        virtual void setYVelocity(float yVelocity) { this->yVelocity = yVelocity; }

    protected:
        // x
        float x;
        // y
        float y;
        // xvelocity
        float xVelocity;
        // yvelocity
        float yVelocity;

    // **************
    // * PROPERTIES *
    // **************

    public:
        //! Get Health
        virtual int getHealth() { return this->health; }
        //! Set Health
        virtual void setHealth(int health) { this->health = health; }
        //! Get Max Health
        virtual int getMaxHealth() { return this->maxHealth; }
        //! Set Max Health
        virtual void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
        //! Get radius
        virtual float getRadius() { return radius; }
        //! Set radius
        virtual void setRadius(float radius) { this->radius = radius; }

    protected:
        // health
        int health;
        // max health
        int maxHealth;
        // radius
        float radius;

    // *********
    // * STATE *
    // *********

    public:
        //! Get State
        virtual std::string getState() { return this->state; }
        //! Set State
        virtual void setState(std::string state) { this->state = state; }

    protected:
        // state
        std::string state;

    // ***********
    // * VISIBLE *
    // ***********

    public:
        //! Is Visible
        virtual bool isVisible() { return this->visibleFlag; }
        //! SetVisible
        virtual void setVisible(bool visibleFlag) { this->visibleFlag = visibleFlag; }

    protected:
        // visible flag
        bool visibleFlag;
// TODO: implement Custom Properties system
//    // *********************
//    // * CUSTOM PROPERTIES *
//    // *********************
//    public:
//        //! Think for the Properties
//        virtual void thinkProperties();
//        //! Update the Properties
//        virtual void updateProperties(float dTime);
//        //! Clear all the property maps
//        virtual void clearProperties();
//        //! Free all the Properities
//        virtual void freeProperties();
//        //! Restore all properties to default values
//        virtual void resetProperties();
//        //! Start all Properties
//        virtual void startProperties();
//        //! Stop all Properties
//        virtual void stopProperties();
//        //! Pause all Properties
//        virtual void pauseProperties();
//        //! Resume all Properties
//        virtual void resumeProperties();
//        //! Send Properties to the Console
//        virtual void propertiesToConsole();
//
//    // FLOATS
//    public:
//        //! Add a float to the floatMap
//        virtual bool addFloat(std::string keyname, float value);
//        //! Is there a float by this name in the floatMap
//        virtual bool isFloat(std::string keyname);
//        //! Remove a float from the floatMap (removes current and default values)
//        virtual void removeFloat(std::string keyname);
//        //! Update Floats
//        virtual void updateFloats(float dTime);
//        //! Clear all floats in the floatMap (clears current and default values)
//        virtual void clearFloats();
//        //! Send the Float Properties to the Console
//        virtual void floatsToConsole();
//
//    public:
//        //! Get a float from floatMap
//        virtual float getFloat(std::string keyname);
//        //! Set a float in the floatMap
//        virtual void setFloat(std::string keyname, float value);
//        //! Get FloatMap
//        virtual std::map<std::string, float>* getFloats() { return &(this->floatMap); }
//
//    public:
//        //! Get a defaultFloat from defaultFloatMap
//        virtual float getDefaultFloat(std::string keyname);
//        //! Set a defaultfloat in the defaultFloatMap
//        virtual void setDefaultFloat(std::string keyname, float value);
//        //! Get FloatDefaultMap
//        virtual std::map<std::string, float>* getDefaultFloats() { return &(this->floatDefaultMap); }
//        //! Restore Float to Default
//        virtual void restoreFloatToDefault(std::string keyname);
//        //! Restore Floats to Defaults
//        virtual void restoreFloatsToDefaults();
//
//    protected:
//        // A map of floats
//        std::map<std::string, float> floatMap;
//        // A map of default values for our floats
//        std::map<std::string, float> floatDefaultMap;
//
//    // DOUBLES
//    public:
//        //! Add a Double to the doubleMap
//        virtual bool addDouble(std::string keyname, double value);
//        //! Is there a double by this name in the doubleMap
//        virtual bool isDouble(std::string keyname);
//        //! Remove a double from the doubleMap
//        virtual void removeDouble(std::string keyname);
//        //! Update Doubles
//        virtual void updateDoubles(float dTime);
//        //! Clear all doubles in the doubleMap
//        virtual void clearDoubles();
//        //! Send the Double Properties to the Console
//        virtual void doublesToConsole();
//
//    public:
//        //! Get a double from doubleMap
//        virtual double getDouble(std::string keyname);
//        //! Set a double in the doubleMap
//        virtual void setDouble(std::string keyname, double value);
//        //! Get Doubles
//        virtual std::map<std::string, double>* getDoubles() { return &(this->doubleMap); }
//
//    public:
//        //! Get a defaultDouble from defaultDoubleMap
//        virtual float getDefaultDouble(std::string keyname);
//        //! Set a defaultDouble in the defaultDoubleMap
//        virtual void setDefaultDouble(std::string keyname, float value);
//        //! Get doubleDefaultMap
//        virtual std::map<std::string, double>* getDefaultDoubles() { return &(this->doubleDefaultMap); }
//        //! Restore Double to Default
//        virtual void restoreDoubleToDefault(std::string keyname);
//        //! Restore doubles to Defaults
//        virtual void restoreDoublesToDefaults();
//
//    protected:
//        // A map of doubles
//        std::map<std::string, double> doubleMap;
//        // A map of default values for our doubles
//        std::map<std::string, double> doubleDefaultMap;
//
//    // SHORT INTEGERS
//    public:
//        //! Add a short int to the shortIntMap
//        virtual bool addShortInt(std::string keyname, short int value);
//        //! Is there a short int by this name in the shortIntMap
//        virtual bool isShortInt(std::string keyname);
//        //! Remove a int from the shortIntMap
//        virtual void removeShortInt(std::string keyname);
//        //! Update Short Ints
//        virtual void updateShortInts(float dTime);
//        //! Clear all Short Ints in the shortIntMap
//        virtual void clearShortInts();
//        //! Send Short Ints to the Console
//        virtual void shortIntsToConsole();
//
//    public:
//        //! Get a int from shortIntMap
//        virtual short int getShortInt(std::string keyname);
//        //! Set a short int in the shortIntMap
//        virtual void setShortInt(std::string keyname, short int value);
//        //! Get shortIntMap
//        virtual std::map<std::string, short int>* getShortInts() { return &(this->shortIntMap); }
//
//    public:
//        //! Get a int from shortIntMap
//        virtual short int getDefaultShortInt(std::string keyname);
//        //! Set a short int in the shortIntMap
//        virtual void setDefaultShortInt(std::string keyname, short int value);
//        //! Get shortIntMap
//        virtual std::map<std::string, short int>* getDefaultShortInts() { return &(this->shortIntMap); }
//        //! Restore Short Int to Default
//        virtual void restoreShortIntToDefault(std::string keyname);
//        //! Restore shortInts to Defaults
//        virtual void restoreShortIntsToDefaults();
//
//    protected:
//        // A map of short ints
//        std::map<std::string, short int> shortIntMap;
//        // A map of default values for our short ints
//        std::map<std::string, short int> shortIntDefaultMap;
//
//    // INTEGERS
//    public:
//        //! Add a int to the intMap
//        virtual bool addInt(std::string keyname, int value);
//        //! Is there a int by this name in the intMap
//        virtual bool isInt(std::string keyname);
//        //! Remove a int from the intMap
//        virtual void removeInt(std::string keyname);
//        //! Update Ints
//        virtual void updateInts(float dTime);
//        //! Clear all ints in the intMap
//        virtual void clearInts();
//        //! Send Ints to the Console
//        virtual void intsToConsole();
//
//    public:
//        //! Get a int from intMap
//        virtual int getInt(std::string keyname);
//        //! Set a int in the intMap
//        virtual void setInt(std::string keyname, int value);
//        //! Get IntMap
//        virtual std::map<std::string, int>* getInts() { return &(this->intMap); }
//
//    public:
//        //! Get a defaultInt from intDefaultMap
//        virtual int getDefaultInt(std::string keyname);
//        //! Set a defaultInt in the defaultIntMap
//        virtual void setDefaultInt(std::string keyname, int value);
//        //! Get defaultIntMap
//        virtual std::map<std::string, int>* getDefaultInts() { return &(this->intDefaultMap); }
//        //! Restore Int to Default
//        virtual void restoreIntToDefault(std::string keyname);
//        //! Restore ints to Defaults
//        virtual void restoreIntsToDefaults();
//
//    protected:
//        // A map of ints
//        std::map<std::string, int> intMap;
//        // A map of default values for our ints
//        std::map<std::string, int> intDefaultMap;
//
//    // UNSIGNED INTEGERS
//    public:
//        //! Add a unsigned int to the unsignedIntMap
//        virtual bool addUnsignedInt(std::string keyname, unsigned int value);
//        //! Is there a unsigned int by this name in the unsignedIntMap
//        virtual bool isUnsignedInt(std::string keyname);
//        //! Remove a unsigned int from the unsignedIntMap
//        virtual void removeUnsignedInt(std::string keyname);
//        //! Update Unsigned Ints
//        virtual void updateUnsignedInts(float dTime);
//        //! Clear all unsignedInts in the unsignedIntMap
//        virtual void clearUnsignedInts();
//        //! Send Unsigned Ints to the Console
//        virtual void unsignedIntsToConsole();
//
//    public:
//        //! Get a unsigned int from unsignedIntMap
//        virtual unsigned int getUnsignedInt(std::string keyname);
//        //! Set a unsigned int in the unsignedIntMap
//        virtual void setUnsignedInt(std::string keyname, unsigned int value);
//        //! Get UnsignedIntMap
//        virtual std::map<std::string, unsigned int>* getUnsignedInts() { return &(this->unsignedIntMap); }
//
//    public:
//        //! Get a defaultUnsignedInt from unsignedIntDefaultMap
//        virtual unsigned int getDefaultUnsignedInt(std::string keyname);
//        //! Set a defaultUnsignedInt in the unsignedIntDefaultMap
//        virtual void setDefaultUnsignedInt(std::string keyname, unsigned int value);
//        //! Get UnsignedIntDefaultMap
//        virtual std::map<std::string, unsigned int>* getDefaultUnsignedInts() { return &(this->unsignedIntDefaultMap); }
//        //! Restore Unsigned Int to Default
//        virtual void restoreUnsignedIntToDefault(std::string keyname);
//        //! Restore ints to Defaults
//        virtual void restoreUnsignedIntsToDefaults();
//
//    protected:
//        // A map of unsigned ints
//        std::map<std::string, unsigned int> unsignedIntMap;
//        // A map of default values for our unsigned ints
//        std::map<std::string, unsigned int> unsignedIntDefaultMap;
//
//    // LONG
//    public:
//        //! Add a long to the longMap
//        virtual bool addLong(std::string keyname, long value);
//        //! Is there a long by this name in the longMap
//        virtual bool isLong(std::string keyname);
//        //! Remove a long from the longMap
//        virtual void removeLong(std::string keyname);
//        //! Update Long
//        virtual void updateLongs(float dTime);
//        //! Clear all longs in the longMap
//        virtual void clearLongs();
//        //! Send Longs to the Console
//        virtual void longsToConsole();
//
//    public:
//        //! Get a long from longMap
//        virtual long getLong(std::string keyname);
//        //! Set a long in the longMap
//        virtual void setLong(std::string keyname, long value);
//        //! Get LongMap
//        virtual std::map<std::string, long>* getLongs() { return &(this->longMap);}
//
//    public:
//        //! Get a long from longMap
//        virtual long getDefaultLong(std::string keyname);
//        //! Set a long in the longMap
//        virtual void setDefaultLong(std::string keyname, long value);
//        //! Get LongMap
//        virtual std::map<std::string, long>* getDefaultLongs() { return &(this->longDefaultMap);}
//        //! Restore Long to Default
//        virtual void restoreLongToDefault(std::string keyname);
//        //! Restore longs to Defaults
//        virtual void restoreLongsToDefaults();
//
//    protected:
//        // A map of longs
//        std::map<std::string, long> longMap;
//        // A map of default values for our longs
//        std::map<std::string, long> longDefaultMap;
//
//    // UNSIGNED LONG
//    public:
//        //! Add a unsigned long to the unsignedlongMap
//        virtual bool addUnsignedLong(std::string keyname, unsigned long value);
//        //! Is there a unsigned long by this name in the unsignedlongMap
//        virtual bool isUnsignedLong(std::string keyname);
//        //! Remove a unsigned long from the unsignedlongMap
//        virtual void removeUnsignedLong(std::string keyname);
//        //! Update Unsigned Long
//        virtual void updateUnsignedLongs(float dTime);
//        //! Clear all unsigned longs in the unsigned longMap
//        virtual void clearUnsignedLongs();
//        //! Send Unsigned Longs to the Console
//        virtual void unsignedLongsToConsole();
//
//    public:
//        //! Get a unsigned long from unsignedlongMap
//        virtual unsigned long getUnsignedLong(std::string keyname);
//        //! Set a unsigned long in the unsignedlongMap
//        virtual void setUnsignedLong(std::string keyname, long value);
//        //! Get unsignedLongMap
//        virtual std::map<std::string, unsigned long>* getUnsignedLongs() { return &(this->unsignedLongMap);}
//
//    public:
//        //! Get a unsigned long from unsignedlongMap
//        virtual unsigned long getDefaultUnsignedLong(std::string keyname);
//        //! Set a unsigned long in the unsignedlongMap
//        virtual void setDefaultUnsignedLong(std::string keyname, long value);
//        //! Get unsignedLongDefaultMap
//        virtual std::map<std::string, unsigned long>* getDefaultUnsignedLongs() { return &(this->unsignedLongDefaultMap);}
//        //! Restore Unsigned Long to Default
//        virtual void restoreUnsignedLongToDefault(std::string keyname);
//        //! Restore longs to Defaults
//        virtual void restoreUnsignedLongsToDefaults();
//
//    protected:
//        // A map of unsigned longs
//        std::map<std::string, unsigned long> unsignedLongMap;
//        // A map of default values for our unsigned longs
//        std::map<std::string, unsigned long> unsignedLongDefaultMap;
//
//    // LONG LONG
//    public:
//        //! Add a long long to the longLongMap
//        virtual bool addLongLong(std::string keyname, long long value);
//        //! Is there a long long by this name in the longLongMap
//        virtual bool isLongLong(std::string keyname);
//        //! Remove a long long from the longLongMap
//        virtual void removeLongLong(std::string keyname);
//        //! Update Long Long
//        virtual void updateLongLongs(float dTime);
//        //! Clear all long longs in the longLongMap
//        virtual void clearLongLongs();
//        //! Send Long Longs to the Console
//        virtual void longLongsToConsole();
//
//    // CURRENT VALUE
//    public:
//        //! Get a long long from longLongMap
//        virtual long long getLongLong(std::string keyname);
//        //! Set a long long in the longLongMap
//        virtual void setLongLong(std::string keyname, long long value);
//        //! Get the LongLongMap
//        virtual std::map<std::string, long long>* getLongLongs() { return &(this->longLongMap);}
//
//    // DEFAULT VALUE
//    public:
//        //! Get a default Long Long from longLongDefaultMap
//        virtual long long getDefaultLongLong(std::string keyname);
//        //! Set a default long long in the longLongDefaultMap
//        virtual void setDefaultLongLong(std::string keyname, long long value);
//        //! Get the Default LongLongMap
//        virtual std::map<std::string, long long>* getDefaultLongLongs() { return &(this->longLongDefaultMap);}
//        //! Restore Long Long to Default
//        virtual void restoreLongLongToDefault(std::string keyname);
//        //! Restore long longs to Defaults
//        virtual void restoreLongLongsToDefaults();
//
//    protected:
//        // A map of long longs
//        std::map<std::string, long long> longLongMap;
//        // A map of default values for our longs
//        std::map<std::string, long long> longLongDefaultMap;
//
//    // UNSIGNED LONG LONG
//    public:
//        //! Add a unsigned long long to the longLongMap
//        virtual bool addUnsignedLongLong(std::string keyname, unsigned long long value);
//        //! Is there a unsigned long long by this name in the longLongMap
//        virtual bool isUnsignedLongLong(std::string keyname);
//        //! Remove a unsigned long long from the longLongMap
//        virtual void removeUnsignedLongLong(std::string keyname);
//        //! Update Unsigned Long Long
//        virtual void updateUnsignedLongLongs(float dTime);
//        //! Clear all unsigned long longs in the unsignedLongLongMap
//        virtual void clearUnsignedLongLongs();
//        //! Send Unsigned Long Longs to the Console
//        virtual void unsignedLongLongsToConsole();
//
//    public:
//        //! Get a unsigned long long from longLongMap
//        virtual unsigned long long getUnsignedLongLong(std::string keyname);
//        //! Set a unsigned long long in the longLongMap
//        virtual void setUnsignedLongLong(std::string keyname, unsigned long long value);
//        //! Get Unsigned LongLongMap
//        virtual std::map<std::string, unsigned long long>* getUnsignedLongLongs() { return &(this->unsignedLongLongMap);}
//
//    public:
//        //! Get a unsigned long long from longLongDefaultMap
//        virtual unsigned long long getDefaultUnsignedLongLong(std::string keyname);
//        //! Set a unsigned long long in the longLongDefaultMap
//        virtual void setDefaultUnsignedLongLong(std::string keyname, unsigned long long value);
//        //! Get Unsigned LongLongDefaultMap
//        virtual std::map<std::string, unsigned long long>* getDefaultUnsignedLongLongs() { return &(this->unsignedLongLongDefaultMap);}
//        //! Restore Unsigned Long Long to Default
//        virtual void restoreUnsignedLongLongToDefault(std::string keyname);
//        //! Restore unsigned long longs to Defaults
//        virtual void restoreUnsignedLongLongsToDefaults();
//
//    protected:
//        // A map of unsigned long longs
//        std::map<std::string, unsigned long long> unsignedLongLongMap;
//        // A map of default values for our unsigned long longs
//        std::map<std::string, unsigned long long> unsignedLongLongDefaultMap;
//
//    // CHAR
//    public:
//        //! Add a char to the charMap
//        virtual bool addChar(std::string keyname, char value);
//        //! Is there a char by this name in the charMap
//        virtual bool isChar(std::string keyname);
//        //! Remove a char from the charMap
//        virtual void removeChar(std::string keyname);
//        //! Update Char
//        virtual void updateChars(float dTime);
//        //! Clear all Chars in the CharMap
//        virtual void clearChars();
//        //! Send Chars to the Console
//        virtual void charsToConsole();
//
//    public:
//        //! Get a char from charMap
//        virtual char getChar(std::string keyname);
//        //! Set a char in the boolMap
//        virtual void setChar(std::string keyname, char value);
//        //! Get Char
//        virtual std::map<std::string, char>* getChars() { return &(this->charMap); }
//
//    public:
//        //! Get a default char from charMap
//        virtual char getDefaultChar(std::string keyname);
//        //! Set a default char in the boolMap
//        virtual void setDefaultChar(std::string keyname, char value);
//        //! Get Char
//        virtual std::map<std::string, char>* getDefaultChars() { return &(this->charDefaultMap); }
//        //! Restore Char to Default
//        virtual void restoreCharToDefault(std::string keyname);
//        //! Restore chars to Defaults
//        virtual void restoreCharsToDefaults();
//
//    protected:
//        // A map of chars
//        std::map<std::string, char> charMap;
//        // A map of default values for our chars
//        std::map<std::string, char> charDefaultMap;
//
//    // UNSIGNED CHAR
//    public:
//        //! Add a char to the unsignedCharMap
//        virtual bool addUnsignedChar(std::string keyname, unsigned char value);
//        //! Is there a unsigned char by this name in the unsignedCharMap
//        virtual bool isUnsignedChar(std::string keyname);
//        //! Remove a unsigned char from the unsigned charMap
//        virtual void removeUnsignedChar(std::string keyname);
//        //! Update Unsigned Char
//        virtual void updateUnsignedChars(float dTime);
//        //! Clear all unsigned Chars in the unsigned CharMap
//        virtual void clearUnsignedChars();
//        //! Send Unsigned Chars to the Console
//        virtual void unsignedCharsToConsole();
//
//    public:
//        //! Get a char from unsignedCharMap
//        virtual unsigned char getUnsignedChar(std::string keyname);
//        //! Set a char in the boolMap
//        virtual void setUnsignedChar(std::string keyname, unsigned char value);
//        //! Get Unsigned Char
//        virtual std::map<std::string, unsigned char>* getUnsignedChars() { return &(this->unsignedCharMap); }
//
//    public:
//        //! Get a char from unsignedCharMap
//        virtual unsigned char getDefaultUnsignedChar(std::string keyname);
//        //! Set a char in the boolMap
//        virtual void setDefaultUnsignedChar(std::string keyname, unsigned char value);
//        //! Get Unsigned Char
//        virtual std::map<std::string, unsigned char>* getDefaultUnsignedChars() { return &(this->unsignedCharMap); }
//        //! Restore UnsignedChar to Default
//        virtual void restoreUnsignedCharToDefault(std::string keyname);
//        //! Restore unsigned chars to Defaults
//        virtual void restoreUnsignedCharsToDefaults();
//
//    protected:
//        // A map of chars
//        std::map<std::string, unsigned char> unsignedCharMap;
//        // A map of default values for our chars
//        std::map<std::string, unsigned char> unsignedCharDefaultMap;
//
//    // BOOLS
//    public:
//        //! Add a bool to the boolMap
//        virtual bool addBool(std::string keyname, bool value);
//        //! Is there a bool by this name in the boolMap
//        virtual bool isBool(std::string keyname);
//        //! Remove a bool from the boolMap
//        virtual void removeBool(std::string keyname);
//        //! Update Bools
//        virtual void updateBools(float dTime);
//        //! Clear all bools in the boolMap
//        virtual void clearBools();
//        //! Send Bool to the Console
//        virtual void boolsToConsole();
//
//    public:
//        //! Get a bool from boolMap
//        virtual bool getBool(std::string keyname);
//        //! Set a bool in the boolMap
//        virtual void setBool(std::string keyname, bool value);
//        //! Get Bools
//        virtual std::map<std::string, bool>* getBools() { return &(this->boolMap); }
//
//    public:
//        //! Get a default bool from boolMap
//        virtual bool getDefaultBool(std::string keyname);
//        //! Set a default bool in the boolMap
//        virtual void setDefaultBool(std::string keyname, bool value);
//        //! Get Default Bools
//        virtual std::map<std::string, bool>* getDefaultBools() { return &(this->boolDefaultMap); }
//        //! Restore Bool to Default
//        virtual void restoreBoolToDefault(std::string keyname);
//        //! Restore bools to Defaults
//        virtual void restoreBoolsToDefaults();
//
//    protected:
//        // A map of bools
//        std::map<std::string, bool> boolMap;
//        // A map of default values for our bools
//        std::map<std::string, bool> boolDefaultMap;
//
//    // STRINGS
//    public:
//        //! Add a String to the stringMap
//        virtual bool addString(std::string keyname, std::string value);
//        //! Is there a std::string by this name in the stringMap
//        virtual bool isString(std::string keyname);
//        //! Remove a std::string from the stringMap
//        virtual void removeString(std::string keyname);
//        //! Update String
//        virtual void updateStrings(float dTime);
//        //! Clear all bools in the stringMap
//        virtual void clearStrings();
//        //! Send Strings to the Console
//        virtual void stringsToConsole();
//
//    public:
//        //! Get a std::string from stringMap
//        virtual std::string getString(std::string keyname);
//        //! Set a std::string in the stringMap
//        virtual void setString(std::string keyname, std::string value);
//        //! Get Strings
//        virtual std::map<std::string, std::string>* getStrings() { return &(this->stringMap); }
//
//    public:
//        //! Get a default std::string from stringDefaultMap
//        virtual std::string getDefaultString(std::string keyname);
//        //! Set a default std::string in the stringMap
//        virtual void setDefaultString(std::string keyname, std::string value);
//        //! Get Default Strings
//        virtual std::map<std::string, std::string>* getDefaultStrings() { return &(this->stringDefaultMap); }
//        //! Restore String to Default
//        virtual void restoreStringToDefault(std::string keyname);
//        //! Restore strings to Defaults
//        virtual void restoreStringsToDefaults();
//
//    protected:
//        // A map of strings
//        std::map<std::string, std::string> stringMap;
//        // A map of default values for our strings
//        std::map<std::string, std::string> stringDefaultMap;
};

#endif // GAMEOBJECT_H
