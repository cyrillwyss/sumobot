/*
 * BehaviorProgramming.h
 *
 *  Created on: 20.04.2015
 *      Author: Cyrill
 */

#ifndef BEHAVIORPROGRAMMING_H_
#define BEHAVIORPROGRAMMING_H_

typedef struct Behavior {

	void (*action)(void);
	void (*supress)(void);
	boolean (*takeControle)(void);

} BehaviorT;

void setBehaviors(BehaviorT* behaviors,int behaviorCount);

void startArbitrator(void);

void stopArbitrator(void);

#endif /* BEHAVIORPROGRAMMING_H_ */
