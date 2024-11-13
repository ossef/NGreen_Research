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

##  Contributors & Copyright

- [Youssef AIT EL MAHJOUB](https://github.com/ossef)
- Jean-Michel Fourneau
- Hind Castel-Taleb
- This code is open source. The original documents are [1, 2] and [3].

[1] "Performance and energy efficiency analysis in NGREEN optical network", Youssef AIT EL MAHJOUB, Hind CASTEL-TALEB and Jean-Michel FOURNEAU. In 14th International Conference on Wireless and Mobile Computing, Networking and Communications, WiMob, 2018.

[2] "A numerical approach of the analysis of optical container filling", Youssef AIT EL MAHJOUB, Hind CASTEL-TALEB and Jean-Michel FOURNEAU. In 12th EAI International Conference on Performance Evaluation Methodologies and Tools, ValueTools, 2019.

[3] "Performance evaluation of Green IT networks", Youssef AIT EL MAHJOUB. In Phd-thesis, Chapter 4. [link : hal.science](https://hal.science/tel-03215137v1), 2021.
