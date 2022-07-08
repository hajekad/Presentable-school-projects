#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CVATRegister
{
public:
    //CVATRegister(void);
    
    ~CVATRegister(void)
    {
      for(vector < CCompany * >::iterator i = sortedById.begin();
          i != sortedById.end();
          i++)
      {
        delete *i;
      }
    }
    
    bool newCompany(const string & name, const string & addr, const string & taxID)
    {
      bool ret = 1;
      string str1;

      CCompany * newCompany = new CCompany;

      newCompany->capital = 0;
      newCompany->name = name;
      newCompany->addr = addr;
      newCompany->taxID = taxID;

      size_t size = name.length();
      for(size_t i = 0; i < size; i++)
      {
        newCompany->nameUp.push_back(toupper(name.at(i)));
      }

      size = addr.length();
      for(size_t i = 0; i < size; i++)
      {
        newCompany->addrUp.push_back(toupper(addr.at(i)));
      }

      if(insertToVectors(newCompany)) 
      {
        ret = 0;
        cancelCompany(newCompany->taxID);
      }

      return ret;
    }

    bool cancelCompany(const string & taxID)
    {
      if(sortedById.empty()) return 0;
      bool ret = 1;
      CCompany * curr;
      vector < CCompany * >::iterator i;
      
      i = lower_bound(sortedById.begin(), sortedById.end(), taxID, comparID);

      if(i == sortedById.end()) return 0;
      
      curr = *i;

      if(curr->taxID != taxID) return 0;
      
      sortedById.erase(i);

      i = lower_bound(sortedByName.begin(), sortedByName.end(), curr, comparCompany);
      sortedByName.erase(i);

      delete curr;

      return ret;
    }

    bool cancelCompany(const string & name, const string & addr )
    {
      if(sortedByName.empty()) return 0;
      bool ret = 1;
      CCompany * curr;
      CCompany * tmp;
      vector < CCompany * >::iterator i;

      tmp = createTempPointer(name, addr); 

      i = lower_bound(sortedByName.begin(), sortedByName.end(), tmp, comparCompany);
      
      if(i == sortedByName.end())
      {
        delete tmp;
        return 0;
      }

      curr = *i;

      if(curr->nameUp != tmp->nameUp || curr->addrUp != tmp->addrUp)
      {
        delete tmp;
        return 0;
      }

      sortedByName.erase(i);

      i = lower_bound(sortedById.begin(), sortedById.end(), curr->taxID, comparID);
      sortedById.erase(i);

      delete curr;
      delete tmp;

      return ret;
    }

    bool invoice(const string & taxID, unsigned int amount )
    {
      if(sortedById.empty()) return 0;
      CCompany * curr;
      vector < CCompany * >::iterator i;
      vector < unsigned int >:: iterator it;
      
      i = lower_bound(sortedById.begin(), sortedById.end(), taxID, comparID);
      
      if(i == sortedById.end()) return 0;
      
      curr = *i;

      if(curr->taxID != taxID) return 0;
      
      curr->capital += amount;

      it = lower_bound(sortedInvoice.begin(), sortedInvoice.end(), amount);

      sortedInvoice.insert(it, amount);

      return 1;
    }

    bool invoice(const string & name, const string & addr, unsigned int amount)
    {
      if(sortedByName.empty()) return 0;
      CCompany * curr;
      CCompany * tmp;
      vector < CCompany * >::iterator i;
      vector < unsigned int >:: iterator it;

      tmp = createTempPointer(name, addr); 

      i = lower_bound(sortedByName.begin(), sortedByName.end(), tmp, comparCompany);
      
      if(i == sortedByName.end())
      {
        delete tmp;
        return 0;
      }
      curr = *i;

      //cerr << "name: " << name << " addr: " << addr << endl << "currName: " << curr->name << " currAddr: " << curr->addr << endl;
      if(curr->nameUp != tmp->nameUp || curr->addrUp != tmp->addrUp)
      {
        delete tmp;
        return 0;
      }

      curr->capital += amount;

      it = lower_bound(sortedInvoice.begin(), sortedInvoice.end(), amount);

      sortedInvoice.insert(it, amount);
      delete tmp;

      return 1;
    }

    bool firstCompany(string & name, string & addr) const
    {
      if(sortedByName.empty()) return 0;
      bool ret = 1;

      CCompany * curr;

      auto i = sortedByName.begin();

      curr = *i;

      name = curr->name;
      addr = curr->addr;

      return ret;
    }

    bool nextCompany(string & name, string & addr ) const
    {
      if(sortedByName.empty()) return 0;
      bool ret = 1;
      CCompany * curr;
      CCompany * tmp;

      tmp = createTempPointer(name, addr);

      auto i = lower_bound(sortedByName.begin(), sortedByName.end(), tmp, comparCompany);
      if(i + 1 == sortedByName.end())
      {
        delete tmp;
        return 0;
      }

      curr = *i;
      
      if(curr->nameUp != tmp->nameUp || curr->addrUp != tmp->addrUp)
      {
        delete tmp;
        return 0;
      }
      
      i++;

      curr = *i;

      name = curr->name;
      addr = curr->addr;
      
      delete tmp;

      return ret;
    }

    bool audit(const string & taxID, unsigned int & sumIncome) const
    {
      if(sortedById.empty()) return 0;
      const CCompany * curr = getPointer(taxID);

      if(curr == nullptr) return 0;
      if(curr->taxID != taxID) return 0;

      sumIncome = curr->capital;

      return 1;
    }

    bool audit(const string & name, const string & addr, unsigned int & sumIncome) const
    {
      if(sortedByName.empty()) return 0;
      const CCompany * curr = getPointer(name, addr);

      if(curr == nullptr) return 0;
      if(curr->nameUp != ommitCapitalization(name) || curr->addrUp != ommitCapitalization(addr)) return 0;

      sumIncome = curr->capital;

      return 1;
    }

    unsigned int medianInvoice( void ) const
    {
      if(sortedInvoice.empty()) return 0;
      unsigned int ret = 0;
      size_t size = sortedInvoice.size();
      size_t median;

      if(size == 0) return ret;

      median = size / 2;

      ret = sortedInvoice.at(median);

      return ret;
    }

    void printID()
    {
      CCompany * tmp;
      size_t size = sortedById.size();
      
      cerr << "sortedById: " << endl;
      for(size_t i = 0; i < size; i++)
      {
        tmp = sortedById.at(i);
        cerr << "   name: "<< tmp->name << endl << "   addr: " << tmp->addr << endl << "   taxID: " << tmp->taxID << endl << "   capital: " << tmp->capital << endl << endl;
      }
    }

    void printName()
    {
      CCompany * tmp;
      size_t size = sortedByName.size();
      
      cerr << "sortedByName: " << endl;
      for(size_t i = 0; i < size; i++)
      {
        tmp = sortedByName.at(i);
        cerr << "   name: "<< tmp->name << endl << "   addr: " << tmp->addr << endl << "   taxID: " << tmp->taxID << endl << "   capital: " << tmp->capital << endl << endl;
      }
    }

private:
    struct CCompany
    {
      string name;
      string addr;
      string taxID;
      unsigned int capital;
      
      string nameUp;
      string addrUp;
    };

    vector < CCompany * > sortedById;
    vector < CCompany * > sortedByName;
    vector < unsigned int > sortedInvoice;

    string ommitCapitalization(const string & str) const
    {
      string ret;

      size_t size = str.length();
      for(size_t i = 0; i < size; i++)
      {
        ret.push_back(toupper(str.at(i)));
      }

      return ret;
    }

    CCompany * createTempPointer(const string & name, const string & addr)  const
    {
      CCompany * ret = new CCompany;

      size_t size = name.length();
      for(size_t i = 0; i < size; i++)
      {
        ret->nameUp.push_back(toupper(name.at(i)));
      }

      size = addr.length();
      for(size_t i = 0; i < size; i++)
      {
        ret->addrUp.push_back(toupper(addr.at(i)));
      }

      return ret;
    }

    CCompany const * getPointer(const string & taxID) const
    {
      const CCompany * curr;
      
      auto i = lower_bound(sortedById.begin(), sortedById.end(), taxID, comparID);

      if(i == sortedById.end()) return nullptr;

      curr = *i;

      return curr;
    }

    CCompany const * getPointer(const string & name, const string & addr) const
    {
      CCompany * tmp = createTempPointer(name, addr);
      CCompany * curr;

      auto i = lower_bound(sortedByName.begin(), sortedByName.end(), tmp, comparCompany);

      if(i == sortedByName.end()) 
      {
        delete tmp; 
        return nullptr;
      }
      curr = *i;

      delete tmp;

      return curr;
    }

    static bool comparID(const CCompany * a, const string & idNewCompany) 
    {
      return a->taxID < idNewCompany;
    }

    static bool comparCompany(const CCompany * a, const CCompany * currCompany) 
    {
      if(a->nameUp == currCompany->nameUp) return a->addrUp < currCompany->addrUp;
      return a->nameUp < currCompany->nameUp;
    }
    
    bool insertToVectors(CCompany *& newCompany)
    {
      bool ret = 0;
      vector < CCompany * >::iterator i;
      size_t it;
      size_t itt;

      i = lower_bound(sortedById.begin(), sortedById.end(), newCompany->taxID, comparID);
      it = distance(sortedById.begin(), i);
      itt = it;
      sortedById.insert(i, newCompany);
      
      if(it != 0)
      {
        if(sortedById.at(it)->taxID == sortedById.at(it - 1)->taxID)
        {
          ret = 1;
        }
      }
      if(itt != (sortedById.size() - 1))
      {
        if(sortedById.at(itt)->taxID == sortedById.at(itt + 1)->taxID)
        {
          ret = 1;
        }
      }   

      i = lower_bound(sortedByName.begin(), sortedByName.end(), newCompany, comparCompany);
      it = distance(sortedByName.begin(), i);
      itt = it;
      sortedByName.insert(i, newCompany);

      if(it != 0)
      {
        if(sortedByName.at(it)->nameUp == sortedByName.at(it - 1)->nameUp && sortedByName.at(it)->addrUp == sortedByName.at(it - 1)->addrUp)
        {
          ret = 1;
        }
      }
      if(itt != (sortedByName.size() - 1))
      {
        if(sortedByName.at(itt)->nameUp == sortedByName.at(itt + 1)->nameUp && sortedByName.at(itt)->addrUp == sortedByName.at(itt + 1)->addrUp)
        {
          ret = 1;
        }
      }

      return ret;
    }
};

#ifndef __PROGTEST__
int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;
  
  CVATRegister b3;
  assert ( ! b3 . cancelCompany ( "apa_krychle" ) );
  assert ( ! b3 . cancelCompany ( "apa" , "krychle" ) );
  assert ( ! b3 . invoice ( "apa_krychle" , 7777 ) );
  assert ( ! b3 . invoice ( "apa", "krychle" , 7777 ) );
  assert ( ! b3 . audit ( "apa_krychle" , sumIncome ) );
  assert ( ! b3 . audit ( "apa", "krychle" , sumIncome ) );
  assert ( ! b3 . nextCompany ( name, addr ) );
  assert ( ! b3 . firstCompany ( name , addr ) );
  assert ( ! b3 . medianInvoice () );

  assert (   b3 . newCompany ( "ACME", "Thakurova", "666/666" ) );

  assert ( ! b3 . cancelCompany ( "apa_krychle" ) );
  assert ( ! b3 . cancelCompany ( "apa" , "krychle" ) );
  assert ( ! b3 . invoice ( "apa_krychle" , 7777 ) );
  assert ( ! b3 . invoice ( "apa", "krychle" , 7777 ) );
  assert ( ! b3 . audit ( "apa_krychle" , sumIncome ) );
  assert ( ! b3 . audit ( "apa", "krychle" , sumIncome ) );
  
  assert (   b3 . firstCompany ( name , addr ) );
  assert ( ! b3 . nextCompany ( name, addr ) );
  assert ( ! b3 . medianInvoice () );

  assert (   b3 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );

  assert ( ! b3 . cancelCompany ( "apa_krychle" ) );
  assert ( ! b3 . cancelCompany ( "apa" , "krychle" ) );
  assert ( ! b3 . invoice ( "apa_krychle" , 7777 ) );
  assert ( ! b3 . invoice ( "apa", "krychle" , 7777 ) );
  assert ( ! b3 . audit ( "apa_krychle" , sumIncome ) );
  assert ( ! b3 . audit ( "apa", "krychle" , sumIncome ) );
  assert (   b3 . firstCompany ( name , addr ) );
  assert (   b3 . nextCompany ( name, addr ) );
  assert ( ! b3 . nextCompany ( name, addr ) );
  assert ( ! b3 . medianInvoice () );

  CVATRegister b1;

  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . invoice ( "666/666", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

  CVATRegister b2;
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  assert ( b2 . medianInvoice () == 0 );
  assert ( b2 . invoice ( "ABCDEF", 1000 ) );
  assert ( b2 . medianInvoice () == 1000 );
  assert ( b2 . invoice ( "abcdef", 2000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . invoice ( "1234567", 100 ) );
  assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b2 . audit ( "1234567", sumIncome ) );
  assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b2 . cancelCompany ( "1234567" ) );
  assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
