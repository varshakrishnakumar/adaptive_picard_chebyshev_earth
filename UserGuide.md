# Adaptive-Picard-Chebyshev for Propagating Perturbed	Two-Body	Orbits

## Robyn	Woollands &	John	Junkins

## Texas	A&M University,	College	Station,	TX
## May 2017

## Overview

This	algorithm	propagates	orbits	in	the	perturbed	two-body	environment	using	automated	and	
adaptive	tuning	of	segments	and	Chebyshev	polynomial	degree.	The	code	has	the	following	
capability:

1.	Automated	segmentation &	polynomial degree	scheme
2.	Loads	precomputed	matrices	for	desired	N
3.	Warm	&	Hot	starts
4.	Radially	adaptive	gravity
5.	Variable	fidelity	force	model
6.	Quasilinearization	error	feedback
7.	Reosculate	Keplerian	perigee	after	each	orbit
8.	Interpolation

A	test	case	is	presented	the	demonstrates	how	the	algorithm	is	run.	Edit	 **_test.cpp_** to	set	different	
initial	conditions,	propagation	time	and	spherical	harmonic	gravity	degree.

## Compile	&	Run

1. Compile	the	matrix	builder	from	within	/src
    **_>>	make	matrix_builder_**
2. Perform	the	one	time	build	of	the	constant	Picard-Chebyshev	matrices	from	within	/src
    **_>>	./matrix_builder_**
3. Compile	the	propagator	from	within	/src
    **_>>	make_**
4. Propagate	the	test	case	orbit	from	within	/src
    **_>>	./test_**


## Functions

### **\src**

   **adaptive_picard_chebyshev.cpp**

   This	is	the	where	all	operations	take	place	for	performing	the	numerical	integration.


   **c_functions.cpp**

   Performs	some	simple	vector-matrix	operations.


   **chebyshev.cpp**

   Generates	Chebyshev	polynomials	of	the	first	kind.


   **clenshaw_curtis_II.cpp**

   Generates	constant	matrices	for	second	order	Clenshaw-Curtis	Quadrature.


   **ecef2eci.cpp**

   Converts	states	from	the	body	frame	to	the	inertial	frame.


   **eci2ecef.cpp**

   Converts	states	from	the	inertial	frame	to	the	body	frame.


   **EGM2008.cpp**

   Computes the	spherical	harmonic	gravity	for	a	specified	degree	and	order.


   **FandG.cpp**

   Computes	the	analytical	solution	to	the	two-body	problem	in	celestial	mechanics.


   **Interpolate.cpp**

   Interpolates	the	solution	to	output	intervals	(ephemeris) specified	by	the	user.


   **lsq_chebyshev_fit.cpp**

   Builds	least	squares	operator	and	Chebyshev	matrix.


   **makefile**

   File	to	compile	all	the	code.


   **matrix_builder.cpp**

   One	time	build	&	store	constant	matrices	required	for	the	Adaptive	Picard-Chebyshev	
   numerical	integration	method.


   **matrix_loader.cpp**

   Loads	constant	matrices	required	for	the	Adaptive	Picard-Chebyshev	numerical	integration	
   method.


   **perigee_approx.cpp**

   Computes	 the	 approximate	 Keplerian	 perigee	 in	 the	 function	 **_polydegree_segments.cpp_** if	 the	
   starting	 user	 specified initial	 conditions	 do	 not	correspond	 to perigee.	 This	 is	 required	 for	
   computing	the	first	Keplerian	orbit	which	is	used	to	determine	the	number	of	segments	and	
   nodes	that	will	produce	a	solution	that	satisfies	the	user	desired	tolerance.


   **perturbed_gravity.cpp**

   Computes	gravity	using	the	terminal	convergence	approximations	which	greatly	enhances the	
   efficiency	of	the	algorithm.


   **picard_chebyshev_propagator.cpp**

   Propagates	segment	by	segment	from	t0	through	to	tf.

   **picard_error_feedback.cpp**

   Computes	the	linear	error	correction	term	that	accelerates Picard	iteration.


   **picard_iteration.cpp**

   Iterates	one	segment	at	a	time	until	convergence.


   **polydegree_segments.cpp**

   Computes	the	number	of	segments	per	orbit	and	the	degree	of	the	Chebyshev	polynomial	
   required	to	fit	acceleration	to	the	user	desired	precision.


   **prepare_propagator.cpp**

   Loads	matrices	for	the	correct	polynomial	degree	and	computes	the	start	and	send	times	for	
   each	segment.


   **radial_gravity.cpp**

   Computes	the	required	gravity	degree	based	on	the	distance	from	the	surface	of Mars.


   **reosc_perigee.cpp**

   Reosculates	Keplerian	perigee	at	the	end	of	each	orbit.


   **rv2elm.cpp**

   Converts	Cartesian	to	Keplerian	orbit	elements.


   **test.cpp**

   Sets	up	a	test	case	and	runs	 **_adaptive_picard_chebyshev_**.



### **\inc**

This	folder	contains	all	the	header files	corresponding	to	the	.cpp	sourse	files	in	the	\src	folder.	In	
addition,	 const.h	 is	 also	 located	 in	 this	 folder.	 Const.h	 specifies a	 number	 of	 astrodynamics	
constants.

**\matrices**

This	folder	stores	the	Picard-Chebyshev	matrix	binary	files	after	the	matrix_builder	command	is	
run.


