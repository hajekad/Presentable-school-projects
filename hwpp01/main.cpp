#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <bitset>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace std; 

#endif /* __PROGTEST__ */
static const unsigned short int MAX_CHUNK_SIZE = 4096;

struct CTree
{
  string character;
  bool hasChar = 0;
  
  CTree * exitZero = nullptr;
  CTree * exitOne = nullptr;
};

void printTree(CTree * curr)
{
  if(curr)
  {
    if(curr->hasChar)
    {
      cerr << "|" << curr->character;
      return;
    }

    printTree(curr->exitZero);
    printTree(curr->exitOne);
  }
}

void deleteTree(CTree * curr)
{
  if(curr)
  {
    if(!curr->hasChar)
    {
      deleteTree(curr->exitZero);
      deleteTree(curr->exitOne);
    }

    delete curr;
  }
}

int mltplr(int i, int l)
{
    int k = 1;

    for(int j = 0; j < (l - i); j++)
    {
      k *= 2;
    }

    return k;
}

void getInput(bool & mainRet, vector < bool > & inStream, const char * inFileName)
{
  char character;
  ifstream myFile;
  myFile.open(inFileName);
  if(!myFile.good())
  {
    mainRet = 0;
    return;
  }

  while (myFile.get(character))
  {
    for (int i = 7; i >= 0; i--)
        inStream.push_back(((character >> i) & 1));
  }
}

char getChar(unsigned int & pos, vector < bool > & inStream)
{
  int asciiVal = 0;

  for(int i = 0; i < 8; i++)
  {
    pos++;
    asciiVal += mltplr(i, 7) * inStream.at(pos);
  }

  return asciiVal;
}

CTree * createTree(vector < bool > & inStream, unsigned int & pos, bool & mainRet)
{
  CTree * currNode = new CTree;

  if((pos + 1) >= inStream.size())
  {
    mainRet = 0;
    return currNode;
  }

  if(inStream.at(pos))
  {
    short int repeater = 1;
    short int tmp = pos + 1;

    bool isUtf = 0;

    if(inStream.at(tmp))
    {
      repeater = 0;
      isUtf = 1;

      while(inStream.at(tmp))
      {
        tmp++;
        repeater++;

        if(repeater == 5) break;
      }
    }

    if (isUtf && ( repeater < 2 || repeater == 5 ))
    {
      mainRet = 0;
      return currNode;
    }
    unsigned char temporary;
    char tempor;
    bool notFirst = 0;

    for(int i = 0; i < repeater; i++)
    {
      temporary = getChar(pos, inStream);
      tempor = temporary;

      if(notFirst == 1 && isUtf == 1) 
      {
        if(temporary < 128 || temporary > 191)
        {
          mainRet = 0;
          return currNode;
        }
      }

      notFirst = 1;

      currNode->character.push_back(tempor);
    }

    if(repeater == 4)
    {
     string str;
     int a = 244;
     int b = 144;
     int c = 128;
     int d = 128;

     str.push_back(a);
     str.push_back(b);
     str.push_back(c);
     str.push_back(d);

     if(currNode->character.compare(str) == 0)
      {
        mainRet = 0;
        return currNode;
      }
    }

    currNode->hasChar = 1;
  }
  else
  {
    pos++;
    currNode->exitZero = createTree(inStream, pos, mainRet);
    pos++;
    currNode->exitOne = createTree(inStream, pos, mainRet);
  }

  return currNode;
}

short int evaluateChunk(vector < bool > & inStream, unsigned int & pos)
{
  if(inStream.at(pos))
  {
    pos++;
    return MAX_CHUNK_SIZE;
  }

  short int ret = 0;

  for(int i = 0; i < 12; i++)
  {
    pos++;
    ret += mltplr(i, 11) * inStream.at(pos); 
  }

  pos++;

  return ret;
}

void decodeChunk(bool & mainRet, ofstream & outFile, short int sizeOfChunk, vector < bool > & inStream, unsigned int & pos, CTree * head)
{
  CTree * curr = head;

  for(short int i = 0; i < sizeOfChunk;)
  { 
    if(pos + 1 >= inStream.size() && (sizeOfChunk - i) > 1)
    {
      mainRet = 0;
      return;
    }

    if(curr->hasChar)
    {
      i++;
      outFile << curr->character;
      if(outFile.fail()) mainRet = 0;
      curr = head;
    }
    else
    {
      if(inStream.at(pos))
      {
        curr = curr->exitOne;
      }
      else
      {
        curr = curr->exitZero;
      }

      pos++;
    }
  }
}

bool decompressFile ( const char * inFileName, const char * outFileName )
{
  vector < bool > inStream;
  CTree * head = nullptr;

  bool ret = 1;
  unsigned int pos = 0;
  short int sizeOfChunk;

  ofstream outFile;
  outFile.open(outFileName);
  if(!outFile.good()) return false;

  getInput(ret, inStream, inFileName);

  head = createTree(inStream, pos, ret);

  if(ret == 0 || ((inStream.size() - pos) < 8))
  {
    deleteTree(head);
    return false;
  }
  pos++;
  
  while(8 < (inStream.size() - pos))
  {
    sizeOfChunk = evaluateChunk(inStream, pos);

    decodeChunk(ret, outFile, sizeOfChunk, inStream, pos, head);
  }  

  outFile.close();

  deleteTree(head);

  if(ret) return true;
  else return false;
}

bool compressFile ( const char * inFileName, const char * outFileName )
{
  // keep this dummy implementation (no bonus) or implement the compression (bonus)
  return false;
}
#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
  ifstream myFile1;
  ifstream myFile2; 
  myFile1.open(fileName1);
  myFile2.open(fileName2);  

  string str1;
  string str2;
  char character;
  
  while (myFile1.get(character))
  {
    for (int i = 7; i >= 0; i--)
        str1.push_back(((character >> i) & 1));
  }

  while (myFile2.get(character))
  {
    for (int i = 7; i >= 0; i--)
        str2.push_back(((character >> i) & 1));
  }

  if(str1.compare(str2) != 0) return false;

  return true;
}

int main ( void )
{
  int i = 0;

  assert ( decompressFile ( "tests/test0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test0.orig", "tempfile" ) );
  cerr << "test" << i << " executed correctly" << endl << "---------------------------------------------------" << endl<< endl;
  i++;

  assert ( decompressFile ( "tests/test1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test1.orig", "tempfile" ) );
  cerr << "test" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/test2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test2.orig", "tempfile" ) );
  cerr << "test" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/test3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test3.orig", "tempfile" ) );
  cerr << "test" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/test4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test4.orig", "tempfile" ) );
  cerr << "test" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( ! decompressFile ( "tests/test5.huf", "tempfile" ) );
  cerr << "test" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i = 0;

  assert ( decompressFile ( "tests/extra0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra0.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra1.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++; 

  assert ( decompressFile ( "tests/extra2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra2.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra3.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra4.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra5.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra5.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra6.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra6.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra7.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra7.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++; 

  assert ( decompressFile ( "tests/extra8.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra8.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  assert ( decompressFile ( "tests/extra9.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra9.orig", "tempfile" ) );
  cerr << "test extra" << i << " executed correctly" << endl << "---------------------------------------------------"<< endl<< endl;
  i++;

  return 0;
}
#endif /* __PROGTEST__ */
