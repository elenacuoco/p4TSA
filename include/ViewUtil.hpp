
/**
 *
 *   Copyright (C) 2004 by Giancarlo Cella                                 
 *   giancarlo.cella@pi.infn.it                                            
 *                                                                         
 *   This program is free software; you can redistribute it and/or modify  
 *   it under the terms of the GNU General Public License as published by  
 *   the Free Software Foundation; either version 2 of the License, or     
 *   (at your option) any later version.                                   
 *                                                                         
 *   This program is distributed in the hope that it will be useful,       
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         
 *   GNU General Public License for more details.                          
 *                                                                         
 *   You should have received a copy of the GNU General Public License     
 *   along with this program; if not, write to the                         
 *   Free Software Foundation, Inc.,                                       
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             
 *
 * @file   ViewUtil.hpp
 * @author Giancarlo Cella <giancarlo.cella@pi.infn.it>
 * @date   Sat Nov 13 17:21:06 2004
 * 
 * @brief  Interface for ViewUtil
 */
#ifndef __VIEWUTIL_HPP
#define __VIEWUTIL_HPP

/**
 * @name System includes
 */
//@{


//@}

/**
 * @name Project includes
 */
//@{
#include <AlgoBase.hpp>

//@}

/**
 * @name Local includes
 */
//@{


//@}

/**
 * @name Forward references
 */
//@{


//@}

/** 
 * tsa namespace
 */
namespace tsa {

    /**  
     * @brief This is a short description of the class ViewUtil
     *
     * A more detailed description of ViewUtil start here
     */
    class ViewUtil : public AlgoBase {
    public:

        /**
         * Constructor
         */
        ViewUtil() {
        };

        /**
         * Destructor
         */
        ~ViewUtil() {
        };


        /**
         * @name User interface
         */
        //@{

        static void Join(std::vector<SeqViewComplex>& sl, SeqViewComplex& joined, double start, double sampling, unsigned int length);

        static void Join(std::vector<SeqViewDouble>& sl, SeqViewDouble& joined, double start, double sampling, unsigned int length);

        static void Join(SeqViewDouble& s1, SeqViewDouble& s2, SeqViewDouble& joined);

        static void Append(SeqViewDouble& s1, SeqViewDouble& s2);

        static void Print(SeqViewDouble& s1, char *filename);

        static void Print(SeqViewComplex& s1, char *filename);

        static void Print(SeqViewDouble& s1);

        static void Range(SeqViewDouble& s1, int l, int m);

        static void Range(SeqViewComplex& s1, int l, int m);

        static void Range(SeqViewDouble& s1, SeqViewDouble& s2, int l, int m);

        static void LeftShift(SeqViewDouble& seq, SeqViewDouble& ins);

        static void PadLeft(SeqViewDouble& src, SeqViewDouble& dst, unsigned int size, double value = 0.0);

        static void PadRight(SeqViewDouble& src, SeqViewDouble& dst, unsigned int size, double value = 0.0);

        static double Dot(SeqViewDouble& s1, unsigned int ch1, SeqViewDouble& s2, unsigned int ch2);

        static void SumChannels(SeqViewDouble& s1, SeqViewDouble& sum);

        static void SumChannels(SeqViewDouble& s1, SeqViewDouble& sum, double wfirst, double wothers);

        static void Fill(SeqViewDouble& ts, double value);
        static void FillSeq(SeqViewDouble& ts, unsigned int i, unsigned int j, double value);

        /** 
         * Extract from the src view the data included in a given time range, tstart<=t<=tend,
         * and put it in the dst view. 
         * 
         * @param src the source view
         * @param dst the destination view
         * @param tstart start time of the range
         * @param tend end time for the range
         * 
         * @return true if the range is fully inside src, false otherwise
         */
        static bool PeekRange(SeqViewDouble& src, SeqViewDouble& dst, double tstart, double tend);

        static void Apply(double (*func)(double), SeqViewDouble& ts);

        static void Apply(double (*func)(double), SeqViewDouble& ts, SeqViewDouble& res);

        static void BinOp(std::complex<double> (*func)(std::complex<double>, std::complex<double>), SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);

        static void BinOp(double (*func)(double, double), SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res);



        static void Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs);

        static void Apply(std::complex<double> (*func)(std::complex<double>), SeqViewComplex& fs, SeqViewComplex& res);

        static void Sum(SeqViewDouble& res, double scale, SeqViewDouble& ts);

        static void Sum(SeqViewComplex& res, double scale, SeqViewComplex& ts);

        static void Inverse(SeqViewDouble& ts1, SeqViewDouble& res);

        static void AffineTransformation(SeqViewDouble& ts1, double a, double b, SeqViewDouble& res);

        static void Ratio(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res);
        static void Ratio(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
        static void Ratio(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res);
        static void Ratio(SeqViewComplex& ts1, SeqViewDouble& ts2, SeqViewComplex& res);

        static void ComplexToPolar(SeqViewComplex& ts1, SeqViewDouble& ts2);

        static void Norm(SeqViewComplex& ts1, SeqViewDouble& res);
        static void Abs(SeqViewComplex& ts1, SeqViewDouble& res);

        static void Abs2(SeqViewComplex& ts1, SeqViewDouble& res);

        static void Prod(SeqViewDouble& ts1, SeqViewDouble& ts2, SeqViewDouble& res);

        static void Prod(SeqViewDouble& ts1, SeqViewComplex& ts2, SeqViewComplex& res);

        static void ProdConj(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);

        static void Phase(SeqViewComplex& ts1, SeqViewComplex& ts2, SeqViewComplex& res);

        static void BlockSum(SeqViewComplex& in, SeqViewComplex& out, int bsize);

        static std::complex<double> Integrate(SeqViewComplex& data, double f1, double f2);

        static double Integrate(SeqViewDouble& data, double f1, double f2);

        static std::complex<double> DelayIntegrate(SeqViewComplex& data, double tau, double f1, double f2);

        static std::complex<double> DelayIntegrate(SeqViewDouble& data, double tau, double f1, double f2);

        static void Multiply(SeqViewDouble& in1, SeqViewDouble& in2, SeqViewDouble& res);
        static void Multiply(SeqViewDouble& in1, SeqViewComplex& in2, SeqViewComplex& res);
        static void Multiply(SeqViewComplex& in1, SeqViewComplex& in2, SeqViewComplex& res);


        //@}


        /**
         * @name Operations
         */
        //@{



        //@}

        /**
         * @name Getters
         */
        //@{

        //@} 

        /**
         * @name Setters
         */
        //@{

        //@}


    protected:

    private:

    };

    /**
     * @name Inline methods
     */
    //@{

    //@}


    /** 
     * @name External references
     */
    //@{

    //@}


} // end namespace tsa

#endif // __VIEWUTIL_HPP
