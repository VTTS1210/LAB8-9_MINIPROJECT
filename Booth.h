#pragma once

#include <string>
#include <memory>

using namespace std;


// ============================================================
// Abstract Base Class
// ============================================================

class Booth
{
protected:
    string _id;
    double _area;

    static const double RENT_PER_SQM;

public:
    Booth(const string& id, double area);
    virtual ~Booth();

    string getId() const;
    double getArea() const;

    double rentPrice() const;
    double totalRent() const;

    // Pure virtual functions
    virtual string getType() const = 0;
    virtual double getOtherFee() const = 0;
};


// ============================================================
// Food
// ============================================================

class Food : public Booth
{
private:
    double _coldStorage;

public:
    Food(
        const string& id,
        double area,
        double coldStorage
    );

    string getType() const override;
    double getOtherFee() const override;
};


// ============================================================
// Clothes
// ============================================================

class Clothes : public Booth
{
public:
    Clothes(
        const string& id,
        double area
    );

    string getType() const override;
    double getOtherFee() const override;
};


// ============================================================
// Jewelry
// ============================================================

class Jewelry : public Booth
{
private:
    double _securityFee;

public:
    Jewelry(
        const string& id,
        double area,
        double securityFee
    );

    string getType() const override;
    double getOtherFee() const override;
};


// ============================================================
// Factory Pattern
// ============================================================

class BoothFactory
{
public:
    static unique_ptr<Booth> create(
        const string& type,
        const string& id,
        double area,
        double extraFee
    );
};