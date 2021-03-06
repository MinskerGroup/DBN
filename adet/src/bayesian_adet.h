/////////////////////////////////////////////////////////////
//
//	bayesian_adet.h
//	10.06.2006	djhill1	created
//
/////////////////////////////////////////////////////////////
#ifndef BAYESIAN_ADET_H
#define BAYESIAN_ADET_H

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "main_aux.h"
#include "filefun.h"
#include "kalman.h"
#include "rbpf.h"
#include "rbpf2.h"
#include "rbpf2_mixKF.h"
#include "mathfun.h"

using namespace std;
using namespace math;

int BAYES_ADET(int argc, char **argv, ostream& errMsg);


class bayes_filter{
  friend ostream& operator<<(ostream& o, const bayes_filter& obj ){ return( o ); };
  friend istream& operator>>(istream& o, bayes_filter& obj ){ return( o ); };
  
  public:
    bayes_filter();
 
    bayes_filter( istream& stream );
    
    bayes_filter( const string& s );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a ) = 0;
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter ) = 0;
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter ) = 0;
    
    virtual void Archive( ostream& o )const = 0;
    
  protected:
  
};

class adet_kf: public bayes_filter, kalman_filter {

  public:
    adet_kf();
    
    adet_kf( istream& stream );
    
    adet_kf( const string& );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a );
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter );
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter );
    
    virtual void Archive( ostream& o ) const;
    
  protected:
  
};

class adet_mkf: public bayes_filter, mixKalman_filter {

  public:
    adet_mkf();
    
    adet_mkf( istream& stream );
    
    adet_mkf( const string& );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a );
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter );
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter );
    
    virtual void Archive( ostream& o ) const;
    
  protected:
  
};

class adet_rkf: public bayes_filter, RobustKalman_filter {

  public:
    adet_rkf();
    
    adet_rkf( istream& stream );
    
    adet_rkf( const string& );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a );
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter );
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter );
    
    virtual void Archive( ostream& o ) const;
    
  protected:
  
};

class adet_rbpf: public bayes_filter, rbpf {
   
  public:
    adet_rbpf();
    
    adet_rbpf( istream& o );
    
    adet_rbpf( const string& s );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a );
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter );
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter );
    
    virtual void Archive( ostream& o ) const;
    
  protected:
  
};

class adet_rbpf2: public bayes_filter, rbpf2 {
   
  public:
    adet_rbpf2();
    
    adet_rbpf2( istream& o, int MAPStrat=0 );
    
    adet_rbpf2( const string& s, int MAPStrat=0 );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a );
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter );
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter );
    
    virtual void Archive( ostream& o ) const;
    
  protected:
    vector< int > _discreteKey;
    int DiscreteMAPStrategy;
};

class adet_rbpf2_mixKF: public bayes_filter, rbpf2_mixKF {
   
  public:
    adet_rbpf2_mixKF();
    
    adet_rbpf2_mixKF( istream& o );
    
    adet_rbpf2_mixKF( const string& s );
  
    virtual vector< vector< float > > Filter( const vector< float >& obs, const float& a );
    
    virtual void Learn( const vector< ts_record >& obs, const int maxIter );
    
    virtual void Learn( const vector< vector< ts_record > >& obs, const int maxIter );
    
    virtual void Archive( ostream& o ) const;
    
  protected:
    vector< int > _discreteKey;
    vector< rbpf_mixKF_params > _components;
  
};

#endif
