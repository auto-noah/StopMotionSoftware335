/**
 * @file LindaFactory.h
 * @author Noah Wolff
 *
 * Factory class that builds the Linda character
 */

#ifndef CANADIANEXPERIENCE_LINDAFACTORY_H
#define CANADIANEXPERIENCE_LINDAFACTORY_H

class Actor;


/**
 * Factory class that builds the Linda character
 */
class LindaFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_LINDAFACTORY_H
