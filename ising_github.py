import numpy as np
import matplotlib.pyplot as plt
from numpy.random import rand
import time
from numba import jit
from tqdm import tqdm

@jit(nopython=True)
def inital_state(L):
  """
  """
  random = np.empty((L,L))
  for i in range(L):
    for j in range(L):
        random[i,j] = np.random.random()
  state = 2*random-1
  return state

@jit(nopython=True)
def calc_energy(state,H=0):
  """
  """
  energy = 0
  L = len(state)

  for i in range(L):
    for j in range(L):
      S = state[i,j]
      nb = state[(i+1)%L, j] + state[i,(j+1)%L] + state[(i-1)%L, j] + state[i,(j-1)%L]
      energy = energy + -1*(nb*S + H*S)
      #print("S = ", S, "| nb = ", nb,"| energy = ", energy)
  return energy

@jit(nopython=True)
def calc_mag(state):
  """
  """
  mag = np.sum(state)
  #print("mag = ", mag)
  return mag

@jit(nopython=True)
def mc_move(state,T):
  """
  """
  L = len(state)

  a = np.random.randint(0,L)
  b = np.random.randint(0,L)

  #print(state)
  #print("a = ", a, "| b = ", b)

  s = state[a,b]
  nb = state[(a+1)%L, b] + state[a,(b+1)%L] + state[(a-1)%L, b] + state[a,(b-1)%L]
  dE = 2*s*nb
  dS = 0
  #print("s = ", s, "| nb = ", nb, "| dE = ", dE)

  if dE <= 0:
    s = s*-1
    dS = 2*s

  elif rand() < np.exp(-dE/T):
    s = s*-1
    dS = 2*s
  
  else:
    dE = 0

  state[a,b] = s

  return state,dE,dS

@jit(nopython=True)
def two_dim_ising(L,temp,num_steps):
  """
  """
  N = L**2
  state = inital_state(L)

  #plt.matshow(state,cmap="Greys")
  #plt.show()

  E = calc_energy(state)
  S = calc_mag(state)

  dE = 0
  dS = 0

  E_avg = np.zeros(num_steps)
  S_avg = np.zeros(num_steps)

  E_avg[0] = E
  S_avg[0] = S

  #print("E0 = ", E, "S0 = ", S)

  for i in range(1,num_steps):
    state, dE, dS = mc_move(state,temp)

    #print("dE = ", dE, "dS = ", dS)

    E = E + dE
    S = S + dS

    #print("E = ", E, "S = ", S)

    E_avg[i] = E_avg[i-1] + (E-E_avg[i-1])/(i+1)
    S_avg[i] = S_avg[i-1] + (S-S_avg[i-1])/(i+1)

  S_avg = np.abs(S_avg)/N
  #S_avg = S_avg/N
  E_avg = E_avg/N

  return state,E_avg,S_avg

@jit(nopython=True)
def two_dim_ising_move(L,temp,num_steps):
  """
  """
  state = inital_state(L)
  for i in range(num_steps):
    state, dE, dS = mc_move(state,temp)
  return state

@jit(nopython=True)
def two_dim_ising_state(state,temp,num_steps):
  """
  """
  N = np.size(state)

  #plt.matshow(state,cmap="Greys")
  #plt.show()

  E = calc_energy(state)
  S = calc_mag(state)

  dE = 0
  dS = 0

  E_avg = np.zeros(num_steps)
  S_avg = np.zeros(num_steps)

  E_avg[0] = E
  S_avg[0] = S

  #print("E0 = ", E, "S0 = ", S)

  for i in range(1,num_steps):
    state, dE, dS = mc_move(state,temp)

    #print("dE = ", dE, "dS = ", dS)

    E = E + dE
    S = S + dS

    #print("E = ", E, "S = ", S)

    E_avg[i] = E_avg[i-1] + (E-E_avg[i-1])/(i+1)
    S_avg[i] = S_avg[i-1] + (S-S_avg[i-1])/(i+1)

  S_avg = np.abs(S_avg)/N
  #S_avg = S_avg/N
  E_avg = E_avg/N

  return state,E_avg,S_avg

start = time.time()
T = np.linspace(0.1,4.0,1000)
spins = np.empty((len(T),40,40))
for i in tqdm(range(len(T))):
    spins[i,:,:] = two_dim_ising_move(40,T[i],100000)[0]

end = time.time()

spins = spins.reshape(len(T),40*40).T

plt.matshow(spins,cmap="Greys")
plt.show()

