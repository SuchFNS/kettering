# The Forensic Process

## Last time

* Forensics Introduction
* Fourth Amendment
* Public/Private
* Rules of evidence
* Chain of custody

The forensic process can be remembered by the **three 'A's**
followed by an R

* **Acquisition**
* **Authentication**
* **Analysis**
* Reporting

## A Model for Digital Forensics

* The role of digital foresnics professional is to *gather evidence* to prove
  that a suspect committed a crime or violated a company policy
* Need a **systematic approach**

### Initial Assement

* Assess:
  * Situation
  * Nature of the case
  * Specifics of the case
  * Type of evidence
  * Operating system
  * Known disk format
  * Location of evidencd

### Planning

* Planning includes:
  * How to collected the evidence
  * Preparing the evidence form
  * How to transport the evidence
  * How to secure the evidence

### Resources

Collect what you need, like write blockers inspection tools,
Rasberry Pis, voltage meters, those kinds of things

* Original storage media
* Evidence custody form
* Evidence container for the storage media
* Bit-stream imaging tool
* Forensic workstation to copy and examine your evidence
* Securable evidence locker, cabinet, or safe (evidence bag)

### Evidence Acquisition and Authentication

* Maintaining the *integrity* of the evidence you have gathered
  * Avoid damaging the evidence
  * Preserve the original evidence

### Investigation: Discover, Extract, and Analyze

* Discover and Extract data from:
  * Deleted files, File fragments, and Complete files
  * Deleted files linger
* Analyze the data

### Reporting and Documentation

* Produce a final report
* **Repeatable findings**
  * Repeate the steps and produce the same result
* Should **show conclusive evidence**
  * Suspect did or did not commit a crime or violate a company policy

## Evidence Acquisition and Authentication

The **first step** in the forensic process is aquiring data. You must be able
to get the data without damaging the original data or scene. However, it must
be done concurrently with Authentication, otherwise a lot of time can be wasted,
and it can be difficult to prove that the data is the same as the original

### Purpose of Acquisition

If you forget to turn on some security feature, the data can be changed somehow,
and the trust in your work essentially goes away
There is now way to know if the files changed were relavant to the case at hand.

***Never work on the original content***. Have multiple copies!!!

### Purpose of Authentication

Proves that the collected evidence is **exactly the same** as the original.
How to compare? Compare every bit to show bit to bit correspondence, or compute
a cryptographic hash of both and show they are equal

*Self Note: Cryptographic hashing is different from some forms of hashing
in software engineering. Cryptographic hashing has certain guarantees for
the chance of two hashes colliding, which makes it more trustworthy
than say taking the first bits every time*

### Hash Functions / Message Digests

A hashing algorithm takes (usually) an input of any size, and produces an output
of a fixed size.

* Purposes
  * Uniquely identify data using the data itself as the source
  * Infeasible to find data taht will generate a specific digest
    * Can't process the hash in reverse
  * Infeasible to find two messages that will generate the same digest (called
    a collision)
  * The digest changes if the data changes
  * Most resilient hashing algorithms are very good at avoiding collisions

Hashing is **necessarily lossy**, as it transforms a space of infinite size
to a space of finite size

Example:
Original message $\rightarrow$ message digest $\Rightarrow$ message
digest output

MD5 produces 128 bit hashes

Example of `sha256`:  
`echo -n "hello" | openssl dgst -sha256` -> some output  

`echo -n "hello" | openssl dgst -sha256` -> same output

`echo -n "password" | openssl dgst -sha256` -> some output

`echo -n "passWord" | openssl dgst -sha256` -> some different output

`echo -n "Some very long message that goes on forever" | openssl dgst -sha256`:
Same size as the rest

#### Algorithms used

* MD5
  * 128 bit
  * Simple, compact, fast
  * Has collision problems
* SHA - 1
  * 160 bit
  * Similar to MD5
* SHA - 2 (family)
  * Includes SHA-256 and SHA-512
  * 256 or 512 bit digest
  * Only has theoretical attacks at present
* SHA - 3
  * 1600 bit digest
  * Provides strong alternative to SHA - 2
  * Became a government standard for information processing when
    approved on August 5, 2015

#### Security Properties of Hash Functions

* Collision resistance - Make it hard to find collisions (hard for things
  like brute force, or give specific inputs)
* Pre-image resistance - It's hard to find some input which gives a
  hash you want produced

  $H(n) = h$ is hard to find for a given $h$
* Second-pre-image resistance - It's hard to find some message which produces
  the same hash as some message you already have

  Find $m' \not= m$ such that $h(m) = h(m')$, given some $m$ and $h$

#### Validation

You can validate that copies are identical by **comparing their hashes**

### Acquisition Types and Methods

Two types:

* Live acquisition
  * System is still running
  * RAM data available
  * Crucial if storage is *encrypted*
* Static (or dead) acquisition
  * System is turned off
  * Preferred
  * Limits data available

Live acquisition over a network is done by streaming a disk image to some server
where it can be inspected further. Static is done usually by removing the disk
from the machine

#### Methods involved

* Logical Acquisition
  * Captures only specific files of interest or specific types of files
  * Focus on filesystem
* Sparse Acquisition
  * Same as logical, but includes fragmented and unallocated data
  * Focus on partition or volume
* Bit-stream Copy/Acquisition
  * Bit-stream disk-to-disk
    * Contents written to an identical disk to make an exact copy (literal duplicate)
  * Disk-to-image
    * Writes the contents to a file rather than a physcial medium

