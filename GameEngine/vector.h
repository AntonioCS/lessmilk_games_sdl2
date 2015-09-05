/* 
 * File:   vector.h
 * Author: antoniocs
 *
 * Created on 25 de Agosto de 2015, 8:48
 */

#ifndef VECTOR_H
#define	VECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        float x;
        float y;
        float z;
    } vector;

    vector *Vector_init();

    void Vector_magnitude(vector *);
    void Vector_normalize(vector *);
    void Vector_reverse(vector *);






#ifdef	__cplusplus
}
#endif

#endif	/* VECTOR_H */

