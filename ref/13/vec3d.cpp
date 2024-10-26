#include <stdio.h>

// Const-correctness

class Vec3d
{
protected:
    double v[3];
public:
	inline Vec3d(){}
	Vec3d(double x,double y,double z);
	Vec3d(const Vec3d &incoming);

    double x(void) const;
    double y(void) const;
    double z(void) const;
    void Set(double x,double y,double z);
};

Vec3d::Vec3d(double x,double y,double z)
{
	Set(x,y,z);
}

Vec3d::Vec3d(const Vec3d &incoming)
{
	Set(incoming.v[0],incoming.v[1],incoming.v[2]);
}

double Vec3d::x(void) const
{
    return v[0];
}

double Vec3d::y(void) const
{
    return v[1];
}

double Vec3d::z(void) const
{
    return v[2];
}

void Vec3d::Set(double x,double y,double z)
{
    v[0]=x;
    v[1]=y;
    v[2]=z;
}

void CrossProduct(Vec3d &crs,const Vec3d &v1,const Vec3d &v2)
{
    // y z x y
    //  * * *
    // y z x y
    //  | | |
    //  X Y Z
    const double x=v1.y()*v2.z()-v1.z()*v2.y();
    const double y=v1.z()*v2.x()-v1.x()*v2.z();
    const double z=v1.x()*v2.y()-v1.y()*v2.x();
    crs.Set(x,y,z);
}

int main(void)
{
    Vec3d v1(1.0,0.0,0.0),v2(0.0,0.0,-1.0),n;
    CrossProduct(n,v1,v2);

    printf("Cross product of (%lf,%lf,%lf)x(%lf,%lf,%lf) is\n",
        v1.x(),v1.y(),v1.z(),v2.x(),v2.y(),v2.z());
    printf(" (%lf,%lf,%lf)\n",n.x(),n.y(),n.z());

    return 0;
}
