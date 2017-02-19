"""
This class implement the clustering of triggers found by wdf pipeline
  .. function:: Cluster(triggers,deltaT)

   :module: pyWDFml.Clustering
"""
import pandas as pd
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class Cluster(object):
    def __init__(self, triggers, deltaT):
        """
        :type deltaT: float
        :type triggers: pandas DataFrame
        """
        self.triggers = triggers
        self.deltaT = deltaT

    def clustering(self):
        col = self.triggers.columns
        clustered_triggers = pd.DataFrame(columns=col)
        duration = 0.0
        delta_t = self.deltaT
        number_clustered_triggers = 0
        k_max = 0
        first = True
        for i in range(len(self.triggers['GPSMax'])):
            if first:
                gps0 = self.triggers['GPSMax'].iloc[i]
                snr_max = self.triggers['SNRMax'].iloc[i]
                duration = 0.0
                first = False
            dt = self.triggers['GPSMax'].iloc[i] - gps0

            if dt <= delta_t:
                duration += dt
                if self.triggers['SNRMax'].iloc[i] >= snr_max:
                    k_max = i
                    snr_max = self.triggers['SNRMax'].iloc[i]

                gps0 = self.triggers['GPSMax'].iloc[i]
                s = pd.Series(self.triggers.loc[k_max].values, index=col)
                s['TDuration'] = duration
                s['GPSstart'] = self.triggers['GPSMax'].iloc[k_max] - duration

            else:
                s = pd.Series(self.triggers.loc[k_max].values, index=col)
                s['TDuration'] = duration
                s['GPSstart'] = self.triggers['GPSMax'].iloc[k_max] - duration
                clustered_triggers = clustered_triggers.append(s, ignore_index=True)
                clustered_triggers['FreqMax'] = clustered_triggers['FreqMax'].map(lambda x: '%4.1f' % float(x))
                clustered_triggers['GPSMax'] = clustered_triggers['GPSMax'].map(lambda x: '%10.7f' % float(x))
                clustered_triggers['GPSstart'] = clustered_triggers['GPSstart'].map(lambda x: '%10.7f' % float(x))
                gps0 = self.triggers['GPSMax'].iloc[i]
                snr_max = self.triggers['SNRMax'].iloc[i]
                k_max=i
                duration=0.0
                number_clustered_triggers += 1
                print(number_clustered_triggers)

        logger.info('Number of triggers: %s' % len(self.triggers))
        logger.info('Number of clustered triggers: %s' % number_clustered_triggers)
        return clustered_triggers

