//
// Created by chenghaowang on 29/03/19.
//

#include <utility>

#include "../include/EvolutionCoursII.h"

EvolutionCoursII::EvolutionCoursII(const PaireDevises &paireDevises) : paireDevises(paireDevises) {}

EvolutionCoursII::EvolutionCoursII(const EvolutionCoursII &e)  : paireDevises(e.getPaireDevises()), nbCours(e.getNbCours()), nbMaxCours(e.getNbMaxCours()),
            cours(new CoursOHLC[e.getNbCours()]){
        for (unsigned int i = 0; i < nbCours; i++)
            cours[i] = e.getCoursAt(i);
}

EvolutionCoursII &EvolutionCoursII::operator=(const EvolutionCoursII &p) {
    if (&p != this) {
        if (nbMaxCours <getNbCours()) {
            delete[] cours;
            cours = new CoursOHLC[p.getNbCours()] ;
            nbMaxCours = p.getNbMaxCours();
        }
        nbCours = p.getNbCours();
        for (unsigned int i = 0; i < nbCours; i++)
            cours[i] = p.getCoursAt(i);
    }
    return *this;
}

void EvolutionCoursII::addCours(double openPrice, double highPrice, double lowPrice, double closePrice, const QDateTime &dateTime) {
    if (nbCours == nbMaxCours) {
        auto * newtab = new CoursOHLC[nbMaxCours + 50];
        for (unsigned int i = 0; i < nbCours; i++)
            newtab[i] = cours[i];
        CoursOHLC* old = cours;
        nbMaxCours += 50;
        cours = newtab;
        delete[] old;
    }
    cours[nbCours++] = CoursOHLC(openPrice, highPrice, lowPrice, closePrice, dateTime);
}

EvolutionCoursII::~EvolutionCoursII() {
    delete[](cours);
}

const PaireDevises &EvolutionCoursII::getPaireDevises() const {
    return paireDevises;
}

CoursOHLC *EvolutionCoursII::getCours() const {
    return cours;
}

unsigned int EvolutionCoursII::getNbMaxCours() const {
    return nbMaxCours;
}

unsigned int EvolutionCoursII::getNbCours() const {
    return nbCours;
}

CoursOHLC& EvolutionCoursII::getCoursAt(int index) const {
    if(index < 0 || index > nbCours - 1) throw  TradingException("out of array!");
    return cours[index];
}

std::ostream &operator<<(std::ostream &os, EvolutionCoursII &i) {
    for(EvolutionCoursII::IteratorII it=i.begin();it!=i.end();++it){
        os<<*it<<"\n";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const EvolutionCoursII &i) {
    for(EvolutionCoursII::ConstIteratorII it=i.begin();it!=i.end();++it){
        os<<*it<<"\n";
    }
    return os;
}



bool EvolutionCoursII::IteratorII::operator==(const EvolutionCoursII::IteratorII &rhs) const {
    return evolutionCours == rhs.evolutionCours &&
           index == rhs.index;
}

bool EvolutionCoursII::IteratorII::operator!=(const EvolutionCoursII::IteratorII &rhs) const {
    return !(rhs == *this);
}

bool EvolutionCoursII::ConstIteratorII::operator==(const EvolutionCoursII::ConstIteratorII &rhs) const {
    return evolutionCours == rhs.evolutionCours &&
           index == rhs.index;
}

bool EvolutionCoursII::ConstIteratorII::operator!=(const EvolutionCoursII::ConstIteratorII &rhs) const {
    return !(rhs == *this);
}
