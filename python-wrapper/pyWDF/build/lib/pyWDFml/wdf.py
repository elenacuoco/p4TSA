__author__ ='Elena Cuoco'
__project__ ='pytsa'

import pytsa


class wdf(object):
    def __init__(self, window,overlap,sampling,threshold,sigma):

        """

        :type sigma: float
        :type threshold: float
        :type sampling: float
        :type overlap: int
        :type window: int


        """
        self.window = window
        self.overlap = overlap
        self.Ncoeff = window
        self.sampling=sampling
        self.threshold=threshold
        self.sigma=sigma

        self.dt = 2.0 * self.window / self.sampling
        self.factorF = self.sampling / (2.0 * self.window)  # to be multiplied by central frequency
        self.DetectD = pytsa.WDF2Classify(self.window, self.overlap, self.threshold, self.sigma, self.Ncoeff)

    def FindEvents(self,data):

        """

        :return: Event over threshold found in the data
        :type data: pytsa.SeqViewDouble()
        :rtype: pytsa.EventFullFeatured
        """
        trigger = pytsa.EventFullFeatured(self.Ncoeff)

        self.DetectD(data,self.sigma)
        self.DetectD(trigger)
        return trigger

