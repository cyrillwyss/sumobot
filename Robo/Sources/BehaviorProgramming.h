/*
 * BehaviorProgramming.h
 *
 *  Created on: 20.04.2015
 *      Author: Cyrill
 */

#ifndef BEHAVIORPROGRAMMING_H_
#define BEHAVIORPROGRAMMING_H_



#define MAXBEHAVIORS 10

typedef struct Behavior {

	void (*init)(void);
	void (*action)(void);
	void (*supress)(void);
	int (*wantsControl)(void);

} BehaviorT;

void BPsetBehaviors(BehaviorT* behaviors,int behaviorCount);

void BPstartArbitrator(void);

void BPstopArbitrator(void);

void BPinit(void);

void BPdeInit(void);

#endif /* BEHAVIORPROGRAMMING_H_ */
