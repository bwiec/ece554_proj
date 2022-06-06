#include "menu.hpp"

menu::menu()
{

}

void menu::print()
{
  print_header();
  cout << "\tMain Menu (type a letter followed by enter):" << endl;
  cout << "c: Channel enable" << endl;
  cout << "s: Sample Rate" << endl;
  cout << "f: Frequency" << endl;
  cout << "p: Pattern" << endl;
  cout << "m: Misc (pattern-specific)" << endl;
  cout << "q: Quit" << endl;
}

void menu::print_header()
{
  cout << "***********************" << endl;
  cout << "* ece554_proj - bwiec *" << endl;
  cout << "***********************" << endl;
  cout << endl;
}

command* menu::get_user_input()
{

}

void menu::prompt()
{
  cout << ">> " << endl;
}

menu::~menu()
{

}