
import numpy
import random
import math
# import numba
import time

class Ising2D:
    def __init__(self,N):
        """
        Initialize the Ising2D class.

        Parameters:
        - N (int): The size of the 2D lattice.

        Returns:
        None
        """
        self.N = N
        self.Ns = N*N
        self.spin = numpy.zeros((N,N),dtype=numpy.uint8)
        self.nbits = 8
        self.Nspin = self.Ns*self.nbits
                
    def temperature(self,T):
        """
        Set the temperature for the Ising model.

        Parameters:
        - T (float): The temperature value.

        Returns:
        None
        """
        beta = 1.0/T
        p0 = math.exp(-8.0*beta)
        p1 = (math.exp(-4.0*beta)-p0)/(1.0-p0)
        self.deuxp0 = p0*2.0
        self.deuxp1 = p1*2.0
     
    def voisin(self,i,j):
        """
        Get the value of the neighboring spin at position (i, j).

        Parameters:
        - i (int): The x-coordinate of the spin.
        - j (int): The y-coordinate of the spin.

        Returns:
        int: The value of the neighboring spin.
        """
        ii = i
        if ii<0:
            ii=self.N-1
        elif ii>=self.N:
            ii=0
        jj = j
        if jj<0:
            jj=self.N-1
        elif jj>=self.N:
            jj=0
        return self.spin[jj][ii]
        
                
    def metropolis(self):
        """
        Perform a Metropolis update on a randomly chosen spin.

        Parameters:
        None

        Returns:
        None
        """
        i = random.randint(0,self.N-1)
        j = random.randint(0,self.N-1)
        s = self.spin[j][i]
        a1 = s^self.voisin(i-1,j)
        a2 = s^self.voisin(i+1,j)
        a3 = s^self.voisin(i,j-1)
        a4 = s^self.voisin(i,j+1)
        R1 = a1|a2|a3|a4
        R2 = ((a1|a2)&(a3|a4))|((a1&a2)|(a3&a4))
        if random.random() < self.deuxp0:
            r0 = random.getrandbits(self.nbits)
        else:
            r0 = 0
        if random.random() < self.deuxp1:
            r1 = random.getrandbits(self.nbits)
        else:
            r1 = 0
        self.spin[j][i] = s^(R2|(R1&r1)|r0)    
                
    def moment(self):
        """
        Calculate the magnetization of the lattice.

        Parameters:
        None

        Returns:
        float: The magnetization value.
        """
        m = 0.0
        for i in range(self.N):
            for j in range(self.N):
                s = self.spin[j][i]
                for b in range(self.nbits):
                    m += 2*(s&1)-1
                    s = s >> 1
        return -m*1.0/self.Nspin
                
    def boucle(self,n):
        """
        Perform a loop of Metropolis updates and calculate the magnetization.

        Parameters:
        - n (int): The number of iterations.

        Returns:
        tuple: A tuple containing the magnetization array, the mean magnetization, and the standard deviation of the magnetization.
        """
        m = numpy.zeros(n,dtype=numpy.float32)
        for k in range(n):
            for l in range(self.Ns):
                self.metropolis()
            m[k] = self.moment()
        return (m,numpy.mean(m),numpy.std(m))
                 
    def couche(self,b):
        """
        Extract a layer of spins from the lattice.

        Parameters:
        - b (int): The bit position of the layer to extract.

        Returns:
        numpy.ndarray: The extracted layer of spins.
        """
        mask = numpy.ones((self.N,self.N),dtype=numpy.uint8)*2**b
        return numpy.bitwise_and(self.spin,mask)

start = time.time()

N = 40
T = 2.3
n = 1000
ising = Ising2D(N)
ising.temperature(T)
(m,moy,sig) = ising.boucle(n)
couche = ising.couche(0)

end = time.time()
print(end - start)

import matplotlib.pyplot as plt
plt.figure()
plt.plot(m)
plt.xlabel('Iterations')
plt.ylabel('Magnetization')
plt.title('Magnetization vs. Iterations')
plt.show()

plt.figure()
plt.imshow(couche)
plt.show()

