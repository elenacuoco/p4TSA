"""Whitening

.. moduleauthor:: Elena Cuoco <elena.cuoco@ego-gw.it>

"""
__author__ ='Elena Cuoco'
__project__ ='pytsa'

import pytsa


class Whitening(object):
    def __init__(self, ARorder):

        """

        :type ARorder: int
         
        """
        self.ARorder = ARorder
        self.ADE = pytsa.ArBurgEstimator(self.ARorder)
        self.LV = pytsa.LatticeView(self.ARorder)
        self.LF = pytsa.LatticeFilter(self.LV)


    def ParameterEstimate(self, data):
        """

        :type data: pytsa.SeqViewDouble
        """
        self.ADE(data)
        self.ADE.GetLatticeView(self.LV)

        return self.ADE, self.LV

    def getSigma(self):
        return self.ADE.GetAR(0)

    def initLatticeFilter(self):
        self.LF.init(self.LV)
        return self.LF


