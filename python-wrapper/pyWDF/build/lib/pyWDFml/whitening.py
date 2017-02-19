"""Whitening

.. moduleauthor:: Elena Cuoco <elena.cuoco@ego-gw.it>

"""
__author__ ='Elena Cuoco'
__project__ ='pynap'

import pynap


class Whitening(object):
    def __init__(self, ARorder):

        """

        :type ARorder: int
         
        """
        self.ARorder = ARorder
        self.ADE = pynap.ArBurgEstimator(self.ARorder)
        self.LV = pynap.LatticeView(self.ARorder)
        self.LF = pynap.LatticeFilter(self.LV)


    def ParameterEstimate(self, data):
        """

        :type data: pynap.SeqViewDouble
        """
        self.ADE(data)
        self.ADE.GetLatticeView(self.LV)

        return self.ADE, self.LV

    def getSigma(self):
        return self.ADE.GetAR(0)

    def initLatticeFilter(self):
        self.LF.init(self.LV)
        return self.LF


