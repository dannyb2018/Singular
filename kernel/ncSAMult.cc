/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/***************************************************************
 *  File:    ncSAMult.cc
 *  Purpose: implementation of multiplication in simple NC subalgebras
 *  Author:  motsak
 *  Created: 
 *  Version: $Id: ncSAMult.cc,v 1.3 2008-07-18 17:12:37 motsak Exp $
 *******************************************************************/


#define MYTEST 1
#define OUTPUT 1

#if MYTEST
#define OM_CHECK 4
#define OM_TRACK 5
#endif

#include "mod2.h"

#include <ncSAMult.h> // for CMultiplier etc classes
#include <sca.h> // for SCA




// poly functions defined in p_Procs: ;
static poly gnc_pp_Mult_mm(const poly p, const poly m, const ring r, poly& last)
{
  assume( (p != NULL) && (m != NULL) && (r != NULL) );

#if OUTPUT  
  Print("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV gnc_pp_Mult_mm(p, m) VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV ");
  PrintLn();
  PrintS("p: "); p_Write(p, r);    
  PrintS("m: "); p_Write(m, r);      
#endif

  
  CGlobalMultiplier* const pMultiplier = r->GetNC()->GetGlobalMultiplier();
  assume( pMultiplier != NULL );

  const poly pResult = pMultiplier->MultiplyPE(p, m);

  p_Test(pResult, r);

#if OUTPUT  
  Print("gnc_pp_Mult_mm(p, m) => "); p_Write(pResult, r);
  PrintS("p: "); p_Write(p, r);    
  PrintS("m: "); p_Write(m, r);      
  Print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ");
  PrintLn();
#endif

  return pResult;

}

static poly gnc_p_Mult_mm(poly p, const poly m, const ring r)
{
  assume( (p != NULL) && (m != NULL) && (r != NULL) );

#if OUTPUT  
  Print("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV gnc_p_Mult_mm(p, m) VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV ");
  PrintLn();
  PrintS("p: ");
  p_Write(p, r);    
  PrintS("m: ");
  p_Write(m, r);  
#endif
  
  CGlobalMultiplier* const pMultiplier = r->GetNC()->GetGlobalMultiplier();
  assume( pMultiplier != NULL );

  const poly pResult = pMultiplier->MultiplyPEDestroy(p, m);

  p_Test(pResult, r);

#if OUTPUT  
  Print("gnc_p_Mult_mm(p, m) => "); p_Write(pResult, r);      
  PrintS("p: "); p_Write(p, r);    
  PrintS("m: "); p_Write(m, r);      
  Print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ");
  PrintLn();
#endif
  
  return pResult;

}

static poly gnc_mm_Mult_p(const poly m, poly p, const ring r)
{
  assume( (p != NULL) && (m != NULL) && (r != NULL) );

  p_Test(m, r);
  p_Test(p, r);

#if OUTPUT  
  Print("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV gnc_mm_Mult_p(m, p) VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV ");
  PrintLn();
  PrintS("m: "); p_Write(m, r);      
  PrintS("p: "); p_Write(p, r);    
#endif
  CGlobalMultiplier* const pMultiplier = r->GetNC()->GetGlobalMultiplier();
  assume( pMultiplier != NULL );

  const poly pResult = pMultiplier->MultiplyEPDestroy(m, p);

  p_Test(pResult, r);

#if OUTPUT  
  Print("gnc_mm_Mult_p(m, p) => "); p_Write(pResult, r);      
  PrintS("p: "); p_Write(p, r);    
  PrintS("m: "); p_Write(m, r);      
  Print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ");
  PrintLn();
#endif
  
  return pResult;
}

static poly gnc_mm_Mult_pp(const poly m, const poly p, const ring r)
{
  assume( (p != NULL) && (m != NULL) && (r != NULL) );

  p_Test(m, r);
  p_Test(p, r);
  
#if OUTPUT  
  Print("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV gnc_mm_Mult_pp(m, p) VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV ");
  PrintLn();
  PrintS("m: "); p_Write(m, r);      
  PrintS("p: "); p_Write(p, r);    
#endif
  

  CGlobalMultiplier* const pMultiplier = r->GetNC()->GetGlobalMultiplier();
  assume( pMultiplier != NULL );

  const poly pResult = pMultiplier->MultiplyEP(m, p);

  p_Test(pResult, r);

#if OUTPUT  
  Print("gnc_mm_Mult_pp(m, p) => "); p_Write(pResult, r);      
  PrintS("p: "); p_Write(p, r);    
  PrintS("m: "); p_Write(m, r);      
  Print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ");
  PrintLn();
#endif
  
  return pResult;
}




static void gnc_p_ProcsSet(ring rGR, p_Procs_s* p_Procs = NULL)
{
#if OUTPUT  
  Print("|gnc_p_ProcsSet()");
  PrintLn();
#endif

  if( p_Procs == NULL )
    p_Procs = rGR->p_Procs;
  
  // "commutative"
  p_Procs->p_Mult_mm  = rGR->p_Procs->p_Mult_mm  = gnc_p_Mult_mm;
  p_Procs->pp_Mult_mm = rGR->p_Procs->pp_Mult_mm = gnc_pp_Mult_mm;

  p_Procs->p_Minus_mm_Mult_qq = rGR->p_Procs->p_Minus_mm_Mult_qq = NULL;

  // non-commutaitve multiplication by monomial from the left
  rGR->GetNC()->p_Procs.mm_Mult_p   = gnc_mm_Mult_p;
  rGR->GetNC()->p_Procs.mm_Mult_pp  = gnc_mm_Mult_pp;

}







bool ncInitSpecialPairMultiplication(ring r)
{
#if OUTPUT  
  Print("ncInitSpecialPairMultiplication(ring), ring: \n");
  rWrite(r);
  PrintLn();
#endif
  
  assume(rIsPluralRing(r));
  assume(!rIsSCA(r));

  r->GetNC()->GetGlobalMultiplier() = new CGlobalMultiplier(r);

  gnc_p_ProcsSet(r);
  return true;
}


CGlobalMultiplier::CGlobalMultiplier(ring r): CMultiplier<poly>(r)
{
#if OUTPUT  
  Print("CGlobalMultiplier::CGlobalMultiplier(ring)!");
  PrintLn();
#endif

  m_cache = new CGlobalCacheHash(r);
  m_powers = new CPowerMultiplier(r);

}


CGlobalMultiplier::~CGlobalMultiplier()
{
#if OUTPUT  
  Print("CGlobalMultiplier::~CGlobalMultiplier()!");
  PrintLn();
#endif

  delete m_cache;
  delete m_powers;
}



// Exponent * Exponent
// TODO: handle components!!!
poly CGlobalMultiplier::MultiplyEE(const CGlobalMultiplier::CExponent expLeft, const CGlobalMultiplier::CExponent expRight)
{

  const ring r = GetBasering();

#if OUTPUT  
  Print("CGlobalMultiplier::MultiplyEE(expLeft, expRight)!");
  PrintLn();
  PrintS("expL: "); p_Write(expLeft, GetBasering());    
  PrintS("expR: "); p_Write(expRight, GetBasering());    
#endif

  CCacheHash<poly>::CCacheItem* pLookup;
  
  int b = m_cache->LookupEE(expLeft, expRight, pLookup);
  // TODO!!!

  // up to now:
  assume( b == -1 );

  // TODO: use PowerMultiplier!!!!

  poly product = NULL;

  const int N = NVars();
  int j = N;
  int i = 1;

  int ej = p_GetExp(expLeft, j, r);
  int ei = p_GetExp(expRight, i, r);

  while( (i < j) && !((ej != 0) && (ei != 0)) )
  {
    if( ei == 0 )
      ei = p_GetExp(expRight, ++i, r);
    
    if( ej == 0 )
      ej = p_GetExp(expLeft, --j, r);
  }

  
#if OUTPUT  
  Print("<CGlobalMultiplier::MultiplyEE>");
  PrintLn();
  Print("i: %d, j: %d", i, j); 
  PrintLn();
  Print("ei: %d, ej: %d", ei, ej); 
  PrintLn();
#endif


  // |  expLeft   | * |  expRight  |
  // |<<<< ej 0..0| , |0..0 ei >>>>|
  // |<<<<  j <<<N| , |1>>>  i >>>>|

  if( i >= j ) // BUG here!!!???
  {
    // either i == j or i = j + 1 => commutative multiple!
    // TODO: it can be done more efficiently! ()
    product = p_Head(expRight, r);

  // |  expLeft     | * |  expRight   |
  // |<<<< ej 0....0| , |0..00 ei >>>>|
  // |<<<<  j i <<<N| , |1>>>j  i >>>>|

    if( i == j )
    {
      if( ej != 0 )
        p_SetExp(product, i, ei + ej, r);
    } // i > j? => nothing to do, just decrement!
      else
        --i;

    for(--i; i > 0; --i)
    {
      const int e = p_GetExp(expLeft, i, r);

      if( e > 0 )
        p_SetExp(product, i, e, r);
    }

    p_Setm(product, r);    

  } else
  { // i < j, ei != 0, ej != 0
    product = m_powers->MultiplyEE( CPower(j, ej), CPower(i, ei) );

#if OUTPUT  
    Print("<CGlobalMultiplier::MultiplyEE> ==> ");
    PrintLn();
    Print("i: %d, j: %d", i, j); 
    PrintLn();
    Print("ei: %d, ej: %d", ei, ej); 
    PrintLn();
    Print("<product>: "); p_Write(product, GetBasering());  
#endif
    

    // TODO: Choose some multiplication strategy!!!
    
    while( (product != NULL) && !((i == NVars()) && (j == 1)) )
    {

      // make some choice here!:

      if( i < NVars() )
      {
        ei = p_GetExp(expRight, ++i, r);
        
        while( (ei == 0) && (i < NVars()) )
          ei = p_GetExp(expRight, ++i, r);

        if( ei != 0 )
          product = m_powers->MultiplyPEDestroy(product, CPower(i, ei));
      } 

      if( j > 1 )
      {
        ej = p_GetExp(expLeft, --j, r);

        while( (ej == 0) && (1 < j) )
          ej = p_GetExp(expLeft, --j, r);

        if( ej != 0 )
          product = m_powers->MultiplyEPDestroy(CPower(j, ej), product);
      }


#if OUTPUT  
      Print("<CGlobalMultiplier::MultiplyEE> ==> ");
      PrintLn();
      Print("i: %d, j: %d", i, j); 
      PrintLn();
      Print("ei: %d, ej: %d", ei, ej); 
      PrintLn();
      Print("<product>: "); p_Write(product, GetBasering());  
#endif
      
    }

  }

  // TODO!      
  

  m_cache->StoreEE( expLeft, expRight, product);
  // up to now:
  return product; 
}

    // Monom * Exponent
poly CGlobalMultiplier::MultiplyME(const poly pMonom, const CGlobalMultiplier::CExponent expRight)
{
#if OUTPUT  
  Print("CGlobalMultiplier::MultiplyME(monom, expR)!");  
  PrintLn();
  PrintS("Monom: "); p_Write(pMonom, GetBasering());    
  PrintS("expR: "); p_Write(expRight, GetBasering());    
#endif

  return MultiplyEE(pMonom, expRight);
}

    // Exponent * Monom
poly CGlobalMultiplier::MultiplyEM(const CGlobalMultiplier::CExponent expLeft, const poly pMonom)
{
#if OUTPUT  
  Print("CGlobalMultiplier::MultiplyEM(expL, monom)!");  
  PrintLn();
  PrintS("expL: "); p_Write(expLeft, GetBasering());    
  PrintS("Monom: "); p_Write(pMonom, GetBasering());    
#endif

  return MultiplyEE(expLeft, pMonom);
}


CCommutativeSpecialPairMultiplier::CCommutativeSpecialPairMultiplier(ring r, int i, int j):
    CSpecialPairMultiplier(r, i, j)
{
#if OUTPUT  
  Print("CCommutativeSpecialPairMultiplier::CCommutativeSpecialPairMultiplier(ring, i: %d, j: %d)!", i, j);
  PrintLn();
#endif
};


CCommutativeSpecialPairMultiplier::~CCommutativeSpecialPairMultiplier()
{
#if OUTPUT  
  Print("CCommutativeSpecialPairMultiplier::~CCommutativeSpecialPairMultiplier()");
  PrintLn();
#endif
}



// Exponent * Exponent
poly CCommutativeSpecialPairMultiplier::MultiplyEE(const int expLeft, const int expRight)
{
#if OUTPUT  
  Print("CCommutativeSpecialPairMultiplier::MultiplyEE(var(%d)^{%d}, var(%d)^{%d})!", GetJ(), expLeft, GetI(), expRight);  
  PrintLn();
#endif

  const ring r = GetBasering();

  poly p = p_ISet(1, r);
  p_SetExp(p, GetJ(), expLeft, r);
  p_SetExp(p, GetI(), expRight, r);
  p_Setm(p, r);

  return p;
}

// factory method!
CSpecialPairMultiplier* AnalyzePair(const ring r, int i, int j)
{
#if OUTPUT  
  Print("AnalyzePair(ring, i: %d, j: %d)!", i, j);
  PrintLn();
#endif

  const int N = r->N;

  assume(i < j);
  assume(i > 0);
  assume(j <= N);


  const poly c = GetC(r, i, j);
  const poly d = GetD(r, i, j);

#if OUTPUT  
  Print("C_{%d, %d} = ", i, j); p_Write(c, r);
  Print("D_{%d, %d} = ", i, j); p_Write(d, r);
#endif

  if( (d == NULL) && n_IsOne(p_GetCoeff(c, r), r) )
    return new CCommutativeSpecialPairMultiplier(r, i, j);

  return NULL;
}






CPowerMultiplier::CPowerMultiplier(ring r): CMultiplier<CPower>(r)
{
#if OUTPUT  
  Print("CPowerMultiplier::CPowerMultiplier(ring)!");
  PrintLn();
#endif

  m_specialpairs = (CSpecialPairMultiplier**)omAlloc0( ((NVars() * (NVars()-1)) / 2) * sizeof(CSpecialPairMultiplier*) );

  for( int i = 1; i < NVars(); i++ )
    for( int j = i + 1; j <= NVars(); j++ )
      GetPair(i, j) = AnalyzePair(GetBasering(), i, j); // factory method!
}


CPowerMultiplier::~CPowerMultiplier()
{
#if OUTPUT  
  Print("CPowerMultiplier::~CPowerMultiplier()!");
  PrintLn();
#endif

  omFreeSize((ADDRESS)m_specialpairs, ((NVars() * (NVars()-1)) / 2) * sizeof(CSpecialPairMultiplier*) );
}


// Monom * Exponent
// pMonom may NOT be of the form: var(j)^{n}!
poly CPowerMultiplier::MultiplyME(const poly pMonom, const CExponent expRight)
{
  const int j = expRight.Var;
  const int n = expRight.Power;

  const ring r = GetBasering();
  
#if OUTPUT  
  Print("CPowerMultiplier::MultiplyME(monom * var(%d)^{%d})!", j, n);
  PrintLn();
  PrintS("Monom: "); p_Write(pMonom, r);  
#endif

  assume( (j > 0) && (j <= NVars()));

  if( n == 0 )
    return p_Head(pMonom, r); // Copy?!?
  

  int v = NVars();
  int e = p_GetExp(pMonom, v, r);

  while((v > j) && (e == 0))
    e = p_GetExp(pMonom, --v, r);

  // TODO: review this!
  if( (v == j) )
  {
    poly p = p_Head(pMonom, r);    
    p_SetExp(p, v, e + n, r);
    p_Setm(p, r);    

    return p;
  }

  assume( v > j );
  assume( e > 0 );
 
  // And now the General Case: v > j!

  poly p = MultiplyEE( CPower(v, e), expRight ); // Easy way!

  --v;
  
  while(v > 0)
  {
    e = p_GetExp(pMonom, v, GetBasering());
    
    if( e > 0 )
      p = MultiplyEPDestroy(CPower(v, e), p);

    --v;
  }

#if OUTPUT  
  Print("CPowerMultiplier::MultiplyME() ===> ");
  p_Write(p, GetBasering());  
#endif
  
  return p;
}

// Exponent * Monom
// pMonom may NOT be of the form: var(i)^{m}!
poly CPowerMultiplier::MultiplyEM(const CExponent expLeft, const poly pMonom)
{
  const ring r = GetBasering();

  // TODO: as above! (difference due to Left/Right semmantics!)
  const int j = expLeft.Var;
  const int n = expLeft.Power;

#if OUTPUT  
  Print("CPowerMultiplier::MultiplyEM(var(%d)^{%d} * monom)!", j, n);
  PrintLn();
  PrintS("Monom: "); p_Write(pMonom, r);  
#endif

  assume( (j > 0) && (j <= NVars()));

  if( n == 0 )
    return p_Head(pMonom, r); // Copy?!?


  int v = 1; // NVars();
  int e = p_GetExp(pMonom, v, r);

  while((v < j) && (e == 0))
    e = p_GetExp(pMonom, ++v, r);

  if( v == j ) 
  {
    poly p = p_Head(pMonom, r);    
    p_SetExp(p, j, e + n, r);
    p_Setm(p, r);    

    return p;
  }

  assume( v < j );
  assume( e > 0 );

  
  // And now the General Case: v > j!

  poly p = MultiplyEE( expLeft, CPower(v, e) ); // Easy way!

  ++v;

  while(v <= NVars())
  {
    e = p_GetExp(pMonom, v, r);
    
    if( e > 0 )
      p = MultiplyPEDestroy(p, CPower(v, e));
          
    ++v;
  }

#if OUTPUT  
  Print("CPowerMultiplier::MultiplyEM() ===> ");
  p_Write(p, r);  
#endif

  return p;
  
}


// Exponent * Exponent
// Computes: var(j)^{expLeft} * var(i)^{expRight}
poly CPowerMultiplier::MultiplyEE(const CExponent expLeft, const CExponent expRight)
{
#if OUTPUT  
  Print("CPowerMultiplier::MultiplyEE)!");
  PrintLn();
#endif

  const int i = expRight.Var, j = expLeft.Var;
  const int ei = expRight.Power, ej = expLeft.Power;

#if OUTPUT  
  Print("Input: var(%d)^{%d} * var(%d)^{%d}", j, ej, i, ei);
  PrintLn();
#endif

  assume(1 <= i);
  assume(j <= NVars());
  assume(1 <= j);
  assume(i <= NVars());
  assume(ei > 0);
  assume(ej > 0);
  
  if( i >= j )
  {
    const ring r = GetBasering();

    poly product = p_ISet(1, r);
    p_SetExp(product, j, ej, r);
    p_SetExp(product, i, ei, r);
    p_Setm(product, r);

    return product;

  } else
  {
    assume(i <  j);

    // No Cache Lookup!? :(

    CSpecialPairMultiplier* pSpecialMultiplier = GetPair(i, j);

    poly product = NULL;

    // Special case?
    if( pSpecialMultiplier != NULL )
    {
      assume( pSpecialMultiplier->GetI() == i );
      assume( pSpecialMultiplier->GetJ() == j );
      assume( pSpecialMultiplier->GetBasering() == GetBasering() );

      return pSpecialMultiplier->MultiplyEE(ej, ei);
    } else
    {
      // Perform general NC Multiplication:
      // TODO

//      product = NULL;
    }
  }
  
  return NULL;  
}






CSpecialPairMultiplier::CSpecialPairMultiplier(ring r, int i, int j):
    CMultiplier<int>(r), m_i(i), m_j(j)
{
#if OUTPUT  
  Print("CSpecialPairMultiplier::CSpecialPairMultiplier(ring, i: %d, j: %d)!", i, j);
  PrintLn();
#endif
  
  assume(i < j);
  assume(i > 0);
  assume(j <= NVars());
}


CSpecialPairMultiplier::~CSpecialPairMultiplier()
{
#if OUTPUT  
  Print("CSpecialPairMultiplier::~CSpecialPairMultiplier()!");
  PrintLn();
#endif
}



// Monom * Exponent
poly CSpecialPairMultiplier::MultiplyME(const poly pMonom, const CExponent expRight)
{
#if OUTPUT  
  Print("CSpecialPairMultiplier::MultiplyME(monom, var(%d)^{%d})!", GetI(), expRight);  
  PrintLn();
  PrintS("Monom: "); p_Write(pMonom, GetBasering());
#endif
  
  return MultiplyEE(p_GetExp(pMonom, GetJ(), GetBasering()), expRight);
}

    // Exponent * Monom
poly CSpecialPairMultiplier::MultiplyEM(const CExponent expLeft, const poly pMonom)
{
#if OUTPUT  
  Print("CSpecialPairMultiplier::MultiplyEM(var(%d)^{%d}, monom)!", GetJ(), expLeft);  
  PrintLn();
  PrintS("Monom: "); p_Write(pMonom, GetBasering());
#endif

  return MultiplyEE(expLeft, p_GetExp(pMonom, GetI(), GetBasering()));
}




