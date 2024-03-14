#include <iostream>
#include <limits>
namespace example
{
  struct SomeStruct
  {
  public:
    SomeStruct(int a, int b):
      a_(a),
      b_(b)
    {}
    int getA() const
    {
      return a_;
    }
    int getB() const
    {
      return b_;
    }
  private:
    int a_, b_;
  };
//(num1;num2)
  std::istream & operator>>(std::istream & is, SomeStruct & value)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    char c = 0;
    is >> c;
    if (c != '(')
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    int a = 0, b = 0;
    is >> a >> c >> b;
    if (c != ';')
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    is >> c;
    if (c!= ')')
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    if (is)
    {
      value = SomeStruct(a, b);
    }
    return is;
  }
  std::ostream & operator<<(std::ostream & out, const SomeStruct & value)
  {
    std::ostream::sentry guard(out);
    if(!guard)
    {
      return out;
    }
    out << "(" << value.getA() << ";" << value.getB() << ")";
    return out;
  }
}
int main()
{
  example::SomeStruct newStruct(0, 0);
  if(!(std::cin >> newStruct))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    if(!(std::cin >> newStruct))
    {
      std::cerr << "Error\n";
    }
  }
  std::cout << newStruct << "\n";
  return 0;
}
