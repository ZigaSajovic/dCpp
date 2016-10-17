#Operational calculus on programming spaces and generalized tensor networks

###Abstract

In this paper, we develop the theory of analytic virtual machines, that
implement analytic programming spaces and operators acting upon them.

A programming space is a subspace of the function space of maps on the virtual
memory. We can construct a differential operator on programming spaces as we 
extend the virtual memory to a tensor product of a virtual space with tensor algebra
of its dual. Extended virtual memory serves by itself as an algebra of programs, giving the expansion of the original program as an infinite tensor series at
program's input values. 

We present a theory of operators on programming spaces, that enables analysis of programs
and computations on the operator level, which favors general implementation. The theory enables
approximation and transformations of programs to a different function basis', allowing us to choose programs' complexity, 
while knowing the order of the error of the approximation. We
also present several examples of how the theory can be used in computer science.

We generalize neural networks by constructing general tensor networks and derive transformations of programs to these trainable networks.
Theory opens new doors in program analysis, while fully retaining algorithmic control flow. We develop a general
procedure which takes a program that tests an object for a property and
constructs a program that imposes that property upon any object. 
We use it to generalize state of the art methods for analyzing neural networks to general programs and tensor networks. Expanding upon them, we study dynamics of computation through principles they induce into the system.

###Implementation

An illustrative example of the implementation of the theory is available at [/ZigaSajovic/dCpp](https://github.com/ZigaSajovic/dCpp). Implementation closely follows theorems and derivations of this paper, intended as an educational guide. A paper explaining the process of implementation accompanies the source-code at [/ZigaSajovic/dCpp/tree/master/paper](https://github.com/ZigaSajovic/dCpp/tree/master/paper). 
