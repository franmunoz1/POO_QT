#include <iostream>
#include <QString>

using namespace std;

namespace ej3 {
QString getVersion() {
    return "1.0";
}

void version(){
    cout << getVersion().toStdString() << endl;
}
}

int main(){
    ej3::version();

    return 0;
}
