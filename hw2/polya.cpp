#include <iostream>
#include "polya.h"
using namespace std;

istream& operator>> (istream& is, Polynomial& p) {
   // terms and (coefficoent, exponent)의 pair들을 읽어들인다.
   // 높은차수의 항부터 저장되었다고 가정한다.
   int noofterms; float coef; int exp;
   is >> noofterms;
   for (int i = 0; i < noofterms; i++) {
      is >> coef >> exp; // 계수와 지수 pair를 읽어들인다.
      p.NewTerm(coef, exp);
   }
   return is;
}
ostream& operator<< (ostream& os, Polynomial& p) {
   float coef;
   int exp;

   for (int i = 0; i < p.terms; i++)
   {
      coef = p.termArray[i].coef;
      exp = p.termArray[i].exp;

      if (coef != 0 && coef != 1 && coef != -1) { // 현재 항의 계수가 0 또는 1 또는 -1이 아닌 경우 계수를 표기
         os << p.termArray[i].coef;
      }
      if(exp == 1) {    // 현재 항이 일차항인 경우 x를 표기
         os << "x";
      }
      if(exp != 0 && exp != 1) {    // 현재 항이 일차항 또는 상수항이 아닌 경우 x^를 표기
         os << "x^" << exp;
      }

      if(i != p.terms - 1) {     // 현재 항이 마지막 항이 아닌 경우
         if (p.termArray[i + 1].coef >= 0) {  // 다음 항의 계수가 0 또는 양수인 경우 공백과 +를 표기
            os << " +";
         }
         else if (i != p.terms - 1 && p.termArray[i + 1].coef == -1) { // 다음 항의 계수가 -1인 경우 공백과 -를 표기
            os << " -";
         }
         else if (p.termArray[i + 1].coef < -1) { // 다음 항의 계수가 음수인 경우 공백만을 표기
            os << " ";
         }
      }
   }
   os << endl;

   return os;
}

Polynomial::Polynomial() :capacity(1), terms(0)
{
   termArray = new Term[capacity];
}
void Polynomial::NewTerm(const float theCoef, const int theExp)
{
   if (terms == capacity) {
      capacity *= 2;
      Term* temp = new Term[capacity];
      copy(termArray, termArray + terms, temp);
      delete[] termArray;
      termArray = temp;
   }
   termArray[terms].coef = theCoef;
   termArray[terms++].exp = theExp;
}
Polynomial Polynomial::operator+(Polynomial& b)
{
   Polynomial c;
   int aPos = 0, bPos = 0;
   while ((aPos < terms) && (bPos < b.terms)) {
      if (termArray[aPos].exp == b.termArray[bPos].exp) {
         float t = termArray[aPos].coef + b.termArray[bPos].coef;
         if (t) {       // t가 0이면 추가하지 않음
               c.NewTerm(t, termArray[aPos].exp);
         }
         aPos++;
         bPos++;
      }
      else if (termArray[aPos].exp < b.termArray[bPos].exp) {
         c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
         bPos++;
      }
      else {
         c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
         aPos++;
      }
   }

   for (; aPos < terms; aPos++) {
      c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
   }

   for (; bPos < b.terms; bPos++) {
      c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
   }
   return c;
}