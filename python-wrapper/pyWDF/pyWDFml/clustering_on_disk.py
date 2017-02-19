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
    def __init__(self, triggers, deltaT, output_file):
        """
        :type deltaT: float
        :type triggers: pandas DataFrame
        :type output_file: string

        """
        self.triggers = triggers
        self.deltaT = deltaT
        self.output_file = output_file


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
            if self.triggers['GPSMax'].iloc[i] - gps0 <= delta_t:
                duration += dt
                if self.triggers['SNRMax'].iloc[i] >= snr_max:
                    k_max = i
		    print ('k_max',k_max) 
                    snr_max = self.triggers['SNRMax'].iloc[i]
                s = pd.Series(self.triggers.loc[k_max].values, index=col)
                s['TDuration'] = duration
                s['GPSstart'] = gps0




            else:

                clustered_triggers = clustered_triggers.append(s, ignore_index=True)
		print ('snr_max: %10.7f'  % s['SNRMax'])
		print ('gps: %10.7f'  %  self.triggers['GPSMax'].iloc[k_max])
	# 
		print ("k_max",k_max)
		raw_input()
		gps0 = self.triggers['GPSMax'].iloc[i]
                snr_max = self.triggers['SNRMax'].iloc[i]
                number_clustered_triggers += 1
                k_max = i
                duration=0.0

                clustered_triggers['FreqMax'] = clustered_triggers['FreqMax'].map(lambda x: '%4.1f' % x)
                clustered_triggers['GPSMax'] = clustered_triggers['GPSMax'].map(lambda x: '%10.7f' % x)
                clustered_triggers['GPSstart'] = clustered_triggers['GPSstart'].map(lambda x: '%10.7f' % x)
                cols = clustered_triggers.columns.tolist()
                cols = cols[-2:] + cols[:-2]

                clustered_triggers = clustered_triggers[cols]

                if i == 1:

                    clustered_triggers.to_csv(self.output_file + '.csv',  index=False)
                else:
                    clustered_triggers.to_csv(self.output_file + '.csv', index=False, mode='a', header=False)

                clustered_triggers = pd.DataFrame(columns=col)


        logger.info('Number of triggers: %s' % len(self.triggers))
        logger.info('Number of clustered triggers: %s' % number_clustered_triggers)
