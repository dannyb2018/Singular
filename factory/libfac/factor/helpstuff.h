////////////////////////////////////////////////////////////
// emacs edit mode for this file is -*- C++ -*-
////////////////////////////////////////////////////////////
#ifndef HELPSTUFF_H
#define HELPSTUFF_H
bool mydivremt ( const CanonicalForm&, const CanonicalForm&, CanonicalForm&, CanonicalForm& );

///////////////////////////////////////////////////////////////
// Now some procedures used in SqrFree and in Factor
///////////////////////////////////////////////////////////////
inline int min ( const int a, const int b ){
  return (a<=b ? a:b);
}
inline int max ( const int a, const int b ){
  return (a>b ? a:b);
}

#endif /* HELPSTUFF_H */

