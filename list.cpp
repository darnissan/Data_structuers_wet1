#include "list.h"

 int IDandTotalPoints::getId() const
    {
        return id;
    }
    int IDandTotalPoints::getTotalPoints() const
    {
        return totalPoints;
    }
    IDandTotalPoints::IDandTotalPoints(int id, int totalPoints) : id(id), totalPoints(totalPoints)
    {
    }
    void IDandTotalPoints::setTotalPoints(int totalPoints)
    {
        this->totalPoints = totalPoints;
    }
    void IDandTotalPoints::setId(int id)
    {
        this->id = id;
    }

    bool IDandTotalPoints::operator==(const IDandTotalPoints &rhs) const
    {
        return id == rhs.id;
    }
    bool IDandTotalPoints::operator!=(const IDandTotalPoints &rhs) const
    {
        return !(rhs.getId() == this->getId());
    }
    bool IDandTotalPoints::operator<(const IDandTotalPoints &rhs) const
    {
        return id < rhs.id;
    }
    bool IDandTotalPoints::operator>(const IDandTotalPoints &rhs) const
    {
        return this->getId() > rhs.getId();
    }
