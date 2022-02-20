#include "stdafx.h"
#include "Control.h"
#include "Window.h"
#include "LineSegment.h"

using namespace std;

int main()
{
    std::string fileName = "input/canvas.txt";
    ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        cout << "Failed to open " << fileName << " for writing\n";
        return 1;
    }
    std::vector<std::shared_ptr<IShape>> shapes;
    CRemoteControl control(inputFile, cout, shapes);
    while (!inputFile.eof() && !inputFile.fail())
    {
        if (!control.HandleCommand())
        {
            cout << "Unknown command!" << endl;
        }
    }
    control.PrintInfo();
    CWindow window;
    window.ShowFixedSize({ 600, 600 });
    window.DoGameLoop(shapes);

    return 0;
}