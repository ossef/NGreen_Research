# NGreen_Research
We model the end to end delay and energy efficiency
in the optical network architecture NGREEN. As the architecture
is based on an optical ring, the random part of the delay comes
from the random times needed to build an optical container from
arriving Data Units and the insertion of the optical container on
the ring. We first build a DTMC (Discrete Time Markov Chain)
to model the filling of the optical container with Data Units.
We take into account a deadline (to have a small latency) and
a constraint on a minimal filling of the container (to be energy
efficient). We obtain through a numerical analysis using an ad-
hoc algorithm we proved, the distribution of the container filling
and the distribution of the time needed to build a container. Then,
we use this distribution to model the inter arrival of optical
containers at a station on the ring. Through simulations and
numerical analysis of Markov chains, we obtain the insertion
delays and the occupancy of the queue before insertion. The
relevance of this work [1] is to propose a trade-off between energy
efficiency and latency for both opportunistic and reservation
insertion modes into the ring. A generalisation to non-stationnary arrivals (i.e. with phase modulating) of data packets for NCD (Near Completely Decomposable) Markov chains is presented in [2].


