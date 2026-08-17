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

    static constexpr double RENT_PER_SQM = 560000;

public:
    Booth(const string& id, double area);
    virtual ~Booth() = default;

    string id() const;
    double area() const;

    double rentPrice() const;
    double totalRent() const;

    virtual string type() const = 0;
    virtual double otherFee() const = 0;
};


// ============================================================
// Food Booth
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

    string type() const override;
    double otherFee() const override;
};


// ============================================================
// Clothes Booth
// ============================================================
class Clothes : public Booth
{
public:
    Clothes(
        const string& id,
        double area
    );

    string type() const override;
    double otherFee() const override;
};


// ============================================================
// Jewelry Booth
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

    string type() const override;
    double otherFee() const override;
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