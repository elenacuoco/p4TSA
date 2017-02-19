import numpy as np
from sklearn import decomposition
from sklearn import neural_network
from sklearn import manifold, preprocessing
import sklearn.mixture  as mix
import matplotlib.pyplot as plt

import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


def gaussian_mixture(matrix, upper_bound):
    '''
    This function clusters the input matrix using the GMM algorithm (gaussian mixture model)
    The number of clusters is found by running the algorithm for n_components = 2 to upper_bound
    and chosing the model which minimized the BIC.

    Returns the labels for each observation.
    :type upper_bound: int
    :param upper_bound: max number of clusters
    
    :type matrix: numpy matrix
    '''
    if (len(matrix) < upper_bound + 1):
        print( "\n\tWARNING: Not enough samples (less than the minimum %i) to run GMM." % (upper_bound))
        print ("\t Only one cluster is returned.\n")
        return [0] * len(matrix)

    j = 0
    lowest_bic = np.infty
    bic = []
    n_components_range = range(1, upper_bound + 1)
    cv_types = ['spherical', 'tied', 'diag', 'full']
    for cv_type in cv_types:
        for n in n_components_range:
            gmm = mix.GMM(n_components=n, covariance_type=cv_type)
            gmm.fit(matrix)
            bic.append(gmm.bic(matrix))
            if bic[-1] < lowest_bic:
                lowest_bic = bic[-1]
                best_gmm = gmm

    best_gmm.fit(matrix)
    res = best_gmm.predict(matrix)

    return res


class WDFMLClassify(object):
    def __init__(self, Waves_Coefficients):
        """


        :type Waves_Coefficients: numpy matrix

        :param Waves_Coefficients: numpy Matrix containing the Wavelets coefficients
        
        """

        self.Waves_Coefficients = Waves_Coefficients

    def PreprocessingSimple(self):
        """
        simple Standard Scaler
        """
        self.X_red = preprocessing.StandardScaler().fit_transform(self.Waves_Coefficients)

        return self.X_red
    def PreprocessingSimplePCA(self,PCA_coefficients,whiten=True):
        """
        simple PCA
        """
        self.PCA_coefficients = PCA_coefficients


        self.pca = decomposition.PCA(n_components=self.PCA_coefficients, whiten=whiten)
        self.X_red =  self.pca.fit_transform(self.Waves_Coefficients)
        return self.X_red

    def PreprocessingEmb(self, MNE_coefficients, N_neighbors):
        """
        :type MNE_coefficients: int

        :param MNE_coefficients: number of coefficients for mns projection

        :param N_neighbors: number of neighbors for embedding
        """
        self.MNE_coefficients = MNE_coefficients

        self.N_neighbors = N_neighbors
        self.X_red = preprocessing.StandardScaler().fit_transform(self.Waves_Coefficients)
        self.Embedding = manifold.SpectralEmbedding(n_components=self.MNE_coefficients,
                                                    affinity='nearest_neighbors',
                                                    gamma=None, random_state=0,
                                                    n_neighbors=self.N_neighbors)

        self.X_red = self.Embedding.fit_transform(self.X_red)
        return self.X_red

    def PreprocessingPCA(self, PCA_coefficients, MNE_coefficients, N_neighbors,whiten=True):
        """
        :type MNE_coefficients: int
        :type PCA_coefficients: int
        :param MNE_coefficients: number of coefficnents for mns projection
        :param PCA_coefficients: number of n_coefficients for PCA transform
        :param N_neighbors: number of neighbors for embedding
        """
        self.MNE_coefficients = MNE_coefficients
        self.PCA_coefficients = PCA_coefficients
        self.N_neighbors = N_neighbors
        self.pca = decomposition.PCA(n_components=self.PCA_coefficients, whiten=whiten)

        self.Embedding = manifold.SpectralEmbedding(n_components=self.MNE_coefficients,
                                                    affinity='nearest_neighbors',
                                                    gamma=None, random_state=11,
                                                    n_neighbors=self.N_neighbors)


        self.X_pca = self.pca.fit_transform(self.Waves_Coefficients)
        self.X_red = self.Embedding.fit_transform(self.X_pca)
        return self.X_red

    def PreprocessingSparsePCA(self, PCA_coefficients, MNE_coefficients, N_neighbors):
        """
        :type MNE_coefficients: int
        :type PCA_coefficients: int
        :param MNE_coefficients: number of coefficnents for mns projection
        :param PCA_coefficients: number of n_coefficients for PCA transform
        :param N_neighbors: number of neighbors for embedding
        """
        self.MNE_coefficients = MNE_coefficients
        self.PCA_coefficients = PCA_coefficients
        self.N_neighbors = N_neighbors

        self.pca = decomposition.SparsePCA(n_components=self.PCA_coefficients,
                                           alpha=0.5, ridge_alpha=0.01, max_iter=1000,
                                           tol=1e-06, method='lars',
                                           n_jobs=-1, U_init=None,
                                           V_init=None, verbose=False,
                                           random_state=0)

        self.Embedding = manifold.SpectralEmbedding(n_components=self.MNE_coefficients,
                                                    affinity='nearest_neighbors',
                                                    gamma=None, random_state=0,
                                                    n_neighbors=self.N_neighbors)
        self.X_pca = self.pca.fit_transform(self.Waves_Coefficients)
        self.X_red = self.Embedding.fit_transform(self.X_pca)
        return self.X_red

    def PreprocessingRandomizedPCA(self, PCA_coefficients, MNE_coefficients, N_neighbors,whiten=True):
        """
        :type MNE_coefficients: int
        :type PCA_coefficients: int
        :param MNE_coefficients: number of coefficnents for mns projection
        :param PCA_coefficients: number of n_coefficients for PCA transform
        :param N_neighbors: number of neighbors for embedding
        """
        self.MNE_coefficients = MNE_coefficients
        self.PCA_coefficients = PCA_coefficients
        self.N_neighbors = N_neighbors

        self.pca = decomposition.RandomizedPCA(n_components=self.PCA_coefficients,whiten=whiten)

        self.Embedding = manifold.SpectralEmbedding(n_components=self.MNE_coefficients,
                                                    affinity='nearest_neighbors',
                                                    gamma=None, random_state=0,
                                                    n_neighbors=self.N_neighbors)
        self.X_pca = self.pca.fit_transform(self.Waves_Coefficients)
        self.X_red = self.Embedding.fit_transform(self.X_pca)
        return self.X_red

    def PreprocessingPCA(self, PCA_coefficients, MNE_coefficients, N_neighbors, whiten=True):
        """
        :type MNE_coefficients: int
        :type PCA_coefficients: int
        :param MNE_coefficients: number of coefficnents for mns projection
        :param PCA_coefficients: number of n_coefficients for PCA transform
        :param N_neighbors: number of neighbors for embedding
        """
        self.MNE_coefficients = MNE_coefficients
        self.PCA_coefficients = PCA_coefficients
        self.N_neighbors = N_neighbors
        self.pca = decomposition.PCA(n_components=self.PCA_coefficients, whiten=whiten)
        # self.pca = decomposition.SparsePCA(n_components=self.PCA_coefficients, random_state=0)

        self.Embedding = manifold.SpectralEmbedding(n_components=self.MNE_coefficients,
                                                    affinity='nearest_neighbors',
                                                    gamma=None, random_state=0,
                                                    n_neighbors=self.N_neighbors)

        self.X_pca = self.pca.fit_transform(self.Waves_Coefficients)
        self.X_red = self.Embedding.fit_transform(self.X_pca)
        return self.X_red

    def PreprocessingRBM(self, components, MNE_coefficients, N_neighbors):
        """
        :type MNE_coefficients: int

        :param MNE_coefficients: number of coefficnents for mns projection

        :param N_neighbors: number of neighbors for embedding
        """
        self.MNE_coefficients = MNE_coefficients

        self.N_neighbors = N_neighbors

        self.rbm = neural_network.BernoulliRBM(n_components=components,
                                               learning_rate=0.05, batch_size=10,
                                               n_iter=100, verbose=0, random_state=0)


        self.Embedding = manifold.SpectralEmbedding(n_components=self.MNE_coefficients,
                                                    affinity='nearest_neighbors',
                                                    gamma=None, random_state=0,
                                                    n_neighbors=self.N_neighbors)
        self.X_rbm = self.rbm.fit_transform(self.Waves_Coefficients)
        self.X_red = self.Embedding.fit_transform(self.X_rbm)
        return self.X_red

    def Classify(self):
        self.labels = gaussian_mixture(self.X_red, 10)
        n_c = len(np.unique(self.labels))
        logger.info('number of clusters: %s' % n_c)
        return self.labels

    def PlotClustering(self):
        plt.figure(figsize=(10, 8))
        plt.xlim(min(self.X_red[:, 0]) - 0.1, max(self.X_red[:, 0]) + 0.1)
        plt.ylim(min(self.X_red[:, 1]) - 0.1, max(self.X_red[:, 1]) + 0.1)

        plt.xticks(fontsize=20)
        plt.yticks(fontsize=20)
        plt.xlabel('Coeff1', fontsize=20)
        plt.ylabel('Coeff2', fontsize=20)
        for i in range(self.X_red.shape[0]):
            plt.text(self.X_red[i, 0], self.X_red[i, 1], str(self.labels[i]),
                     color=plt.cm.spectral(self.labels[i] / 10.),
                     fontdict={'weight': 'bold', 'size': 12})
