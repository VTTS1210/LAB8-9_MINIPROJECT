#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <string>
#include <stdexcept>

#include "Booth.h"

using namespace std;


// ============================================================
// Format money
// Example:
// 560000   -> 560.000
// 43680000 -> 43.680.000
// ============================================================

string formatMoney(double amount)
{
    long long value = static_cast<long long>(amount);

    string number = to_string(value);

    int position = static_cast<int>(number.length()) - 3;

    while (position > 0)
    {
        number.insert(position, ".");
        position -= 3;
    }

    return number;
}


// ============================================================
// Get value after '='
// Example:
// "ID=A724" -> "A724"
// "Area=78" -> "78"
// ============================================================

string getValue(const string& token)
{
    size_t position = token.find('=');

    if (position == string::npos)
    {
        throw invalid_argument(
            "Invalid token: " + token
        );
    }

    return token.substr(position + 1);
}


// ============================================================
// Read booths from file
// ============================================================

vector<unique_ptr<Booth>> readBooths(
    const string& filename
)
{
    ifstream file(filename);

    if (!file)
    {
        throw runtime_error(
            "Cannot open file: " + filename
        );
    }

    vector<unique_ptr<Booth>> booths;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string type;
        string idToken;
        string areaToken;
        string extraToken;

        // Example:
        // Food ID=A724, Area=78, ColdStorage=3000000

        getline(ss, type, ' ');
        getline(ss, idToken, ',');
        getline(ss, areaToken, ',');

        string id = getValue(idToken);

        double area =
            stod(getValue(areaToken));

        double extraFee = 0;

        // Food / Jewelry
        if (getline(ss, extraToken))
        {
            extraFee =
                stod(getValue(extraToken));
        }

        booths.push_back(
            BoothFactory::create(
                type,
                id,
                area,
                extraFee
            )
        );
    }

    return booths;
}


// ============================================================
// Print report
// ============================================================

void printReport(
    const vector<unique_ptr<Booth>>& booths
)
{
    cout << "\n";
    cout << "Bao cao thu tien thue mat bang cho Ben Thanh\n";
    cout << "Thang: 05/2024\n\n";

    cout << left
         << setw(5)  << "STT"
         << " | "
         << setw(7)  << "Ma sap"
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
         << '\n';

    cout << string(112, '-') << '\n';

    double total = 0;

    int stt = 1;

    for (const auto& booth : booths)
    {
        string area =
            to_string(
                static_cast<int>(booth->area())
            ) + " m2";

        cout << left
             << setw(5)
             << stt++

             << " | "

             << setw(7)
             << booth->id()

             << " | "

             << setw(11)
             << booth->type()

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
                    booth->otherFee()
                )

             << " | "

             << setw(14)
             << formatMoney(
                    booth->totalRent()
                )

             << '\n';

        total += booth->totalRent();
    }

    cout << '\n';

    cout << "Tong tien thue mat bang thu trong thang: "
         << formatMoney(total)
         << " d\n";
}


// ============================================================
// Main
// ============================================================

int main()
{
    try
    {
        // Read data
        auto booths =
            readBooths("RentMay24.txt");

        // Sort by total rent ascending
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

        // Print report
        printReport(booths);
    }
    catch (const exception& e)
    {
        cerr << "Error: "
             << e.what()
             << '\n';

        return 1;
    }

    return 0;
}