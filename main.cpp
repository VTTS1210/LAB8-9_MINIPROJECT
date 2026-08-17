#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <memory>
#include <utility>

#include "Booth.h"

using namespace std;


// ============================================================
// Convert string to value after '='
// Example:
// ID=A724  -> A724
// Area=78  -> 78
// ============================================================

string getValue(const string& data)
{
    int position = data.find('=');

    if (position == string::npos)
        return "";

    return data.substr(position + 1);
}


// ============================================================
// Format money
// Example:
// 560000     -> 560.000
// 43680000   -> 43.680.000
// ============================================================

string formatMoney(double money)
{
    long long value = (long long)money;

    string result = to_string(value);

    int position = result.length() - 3;

    while (position > 0)
    {
        result.insert(position, ".");
        position -= 3;
    }

    return result;
}


// ============================================================
// Read booths from file
// ============================================================

vector<unique_ptr<Booth>> readBooths(
    const string& filename
)
{
    vector<unique_ptr<Booth>> booths;

    ifstream file(filename);

    if (!file)
    {
        cout << "Khong the mo file: "
             << filename << endl;

        return booths;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string type;
        string idData;
        string areaData;
        string extraData;

        // ----------------------------------------------------
        // Read type
        // ----------------------------------------------------

        getline(ss, type, ' ');

        // ----------------------------------------------------
        // Read ID
        // ----------------------------------------------------

        getline(ss, idData, ',');

        // ----------------------------------------------------
        // Read Area
        // ----------------------------------------------------

        getline(ss, areaData, ',');

        string id = getValue(idData);

        double area =
            stod(getValue(areaData));

        // ----------------------------------------------------
        // Read additional fee
        // Food:
        // ColdStorage=3000000
        //
        // Jewelry:
        // SecurityFee=7000000
        //
        // Clothes:
        // No additional fee
        // ----------------------------------------------------

        double extraFee = 0;

        if (getline(ss, extraData))
        {
            extraFee =
                stod(getValue(extraData));
        }

        // ----------------------------------------------------
        // Create object using Factory
        // ----------------------------------------------------

        unique_ptr<Booth> booth =
            BoothFactory::create(
                type,
                id,
                area,
                extraFee
            );

        if (booth != nullptr)
        {
            booths.push_back(move(booth));
        }
    }

    file.close();

    return booths;
}


// ============================================================
// Print report
// ============================================================

void printReport(
    const vector<unique_ptr<Booth>>& booths
)
{
    cout << endl;

    cout << "Bao cao thu tien thue mat bang cho Ben Thanh"
         << endl;

    cout << "Thang: 05/2024"
         << endl;

    cout << endl;


    // --------------------------------------------------------
    // Table header
    // --------------------------------------------------------

    cout << left
         << setw(5) << "STT"
         << " | "
         << setw(7) << "Ma sap"
         << " | "
         << setw(11) << "Loai"
         << " | "
         << setw(10) << "Dien tich"
         << " | "
         << setw(10) << "Tien / m2"
         << " | "
         << setw(14) << "Tien mat bang"
         << " | "
         << setw(10) << "Phi khac"
         << " | "
         << setw(14) << "Tong cong"
         << endl;


    cout << string(112, '-')
         << endl;


    // --------------------------------------------------------
    // Print each booth
    // --------------------------------------------------------

    double total = 0;

    int stt = 1;

    for (const auto& booth : booths)
    {
        string area =
            to_string(
                (int)booth->getArea()
            ) + " m2";


        cout << left

             << setw(5)
             << stt

             << " | "

             << setw(7)
             << booth->getId()

             << " | "

             << setw(11)
             << booth->getType()

             << " | "

             << setw(10)
             << area

             << " | "

             << setw(10)
             << formatMoney(560000)

             << " | "

             << setw(14)
             << formatMoney(
                    booth->rentPrice()
                )

             << " | "

             << setw(10)
             << formatMoney(
                    booth->getOtherFee()
                )

             << " | "

             << setw(14)
             << formatMoney(
                    booth->totalRent()
                )

             << endl;


        total += booth->totalRent();

        stt++;
    }


    // --------------------------------------------------------
    // Total
    // --------------------------------------------------------

    cout << endl;

    cout << "Tong tien thue mat bang thu trong thang: "
         << formatMoney(total)
         << " d"
         << endl;
}


// ============================================================
// Main
// ============================================================

int main()
{
    // Read all booths
    vector<unique_ptr<Booth>> booths =
        readBooths("RentMay24.txt");


    // --------------------------------------------------------
    // Sort by total rent in ascending order
    // --------------------------------------------------------

    sort(
        booths.begin(),
        booths.end(),
        [](const unique_ptr<Booth>& a,
           const unique_ptr<Booth>& b)
        {
            return a->totalRent()
                 < b->totalRent();
        }
    );


    // --------------------------------------------------------
    // Print report
    // --------------------------------------------------------

    printReport(booths);


    return 0;
}