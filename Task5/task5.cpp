#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Site
{
    string name;
    string specialization;
    int year;
    int visitors;
    string owner;
};
void AddSite(Site sites[], int& count)
{
    if (count >= 100)
    {
        cout << "Cannot add more sites." << endl;
        return;
    }
    cin.ignore();
    cout << "Enter site name: ";
    getline(cin, sites[count].name);
    cout << "Enter specialization: ";
    getline(cin, sites[count].specialization);
    cout << "Enter year of foundation: ";
    cin >> sites[count].year;
    cout << "Enter average number of visitors: ";
    cin >> sites[count].visitors;
    cin.ignore();
    cout << "Enter owner: ";
    getline(cin, sites[count].owner);
    count++;
    cout << "Site added successfully." << endl;
}
void ShowSites(Site sites[], int count)
{
    if (count == 0)
    {
        cout << "No sites available." << endl;
        return;
    }
    for (int i = 0; i < count; i++)
    {
        cout << "\nSite #" << i + 1 << endl;
        cout << "Name: " << sites[i].name << endl;
        cout << "Specialization: " << sites[i].specialization << endl;
        cout << "Year: " << sites[i].year << endl;
        cout << "Visitors: " << sites[i].visitors << endl;
        cout << "Owner: " << sites[i].owner << endl;
    }
}
void SaveToFile(Site sites[], int count)
{
    ofstream file("sites.txt");
    if (!file.is_open())
    {
        cout << "Error opening file for writing." << endl;
        return;
    }
    file << count << endl;
    for (int i = 0; i < count; i++)
    {
        file << sites[i].name << endl;
        file << sites[i].specialization << endl;
        file << sites[i].year << endl;
        file << sites[i].visitors << endl;
        file << sites[i].owner << endl;
    }
    file.close();
    cout << "Data saved to file." << endl;
}
void LoadFromFile(Site sites[], int& count)
{
    ifstream file("sites.txt");
    if (!file.is_open())
    {
        cout << "Error opening file for reading." << endl;
        return;
    }
    file >> count;
    file.ignore();
    for (int i = 0; i < count; i++)
    {
        getline(file, sites[i].name);
        getline(file, sites[i].specialization);
        file >> sites[i].year;
        file >> sites[i].visitors;
        file.ignore();
        getline(file, sites[i].owner);
    }
    file.close();
    cout << "Data loaded from file." << endl;
}
void ShowThreeLeastVisited(Site sites[], int count)
{
    if (count == 0)
    {
        cout << "No sites available." << endl;
        return;
    }
    Site temp[100];
    for (int i = 0; i < count; i++)
    {
        temp[i] = sites[i];
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (temp[j].visitors > temp[j + 1].visitors)
            {
                Site t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    int limit = count < 3 ? count : 3;
    cout << "\nThree sites with the smallest number of visitors:\n";
    for (int i = 0; i < limit; i++)
    {
        cout << "\nSite #" << i + 1 << endl;
        cout << "Name: " << temp[i].name << endl;
        cout << "Specialization: " << temp[i].specialization << endl;
        cout << "Year: " << temp[i].year << endl;
        cout << "Visitors: " << temp[i].visitors << endl;
        cout << "Owner: " << temp[i].owner << endl;
    }
}
int main()
{
    Site sites[100];
    int count = 0;
    int choice;
    do
    {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Add site" << endl;
        cout << "2. Show all sites" << endl;
        cout << "3. Save to file" << endl;
        cout << "4. Load from file" << endl;
        cout << "5. Show 3 least visited sites" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            AddSite(sites, count);
            break;
        case 2:
            ShowSites(sites, count);
            break;
        case 3:
            SaveToFile(sites, count);
            break;
        case 4:
            LoadFromFile(sites, count);
            break;
        case 5:
            ShowThreeLeastVisited(sites, count);
            break;
        case 0:
            cout << "Program finished." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);
    return 0;
}