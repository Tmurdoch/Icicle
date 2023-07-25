

float GetT( float t, float alpha, const FVector& p0, const FVector& p1 )
{
    auto d  = p1 - p0;
    float a = d | d; // Dot product
    float b = FMath::Pow( a, alpha*.5f );
    return (b + t);
}

/**
 * Catmull-rom spline implementation for unreal engine, pulled from 
 * wikipedia
*/
FVector CatmullRom( const FVector& p0, const FVector& p1, const FVector& p2, const FVector& p3, float t /* between 0 and 1 */, float alpha=.5f /* between 0 and 1 */ )
{
    float t0 = 0.0f;
    float t1 = GetT( t0, alpha, p0, p1 );
    float t2 = GetT( t1, alpha, p1, p2 );
    float t3 = GetT( t2, alpha, p2, p3 );
    t = FMath::Lerp( t1, t2, t );
    FVector A1 = ( t1-t )/( t1-t0 )*p0 + ( t-t0 )/( t1-t0 )*p1;
    FVector A2 = ( t2-t )/( t2-t1 )*p1 + ( t-t1 )/( t2-t1 )*p2;
    FVector A3 = ( t3-t )/( t3-t2 )*p2 + ( t-t2 )/( t3-t2 )*p3;
    FVector B1 = ( t2-t )/( t2-t0 )*A1 + ( t-t0 )/( t2-t0 )*A2;
    FVector B2 = ( t3-t )/( t3-t1 )*A2 + ( t-t1 )/( t3-t1 )*A3;
    FVector C  = ( t2-t )/( t2-t1 )*B1 + ( t-t1 )/( t2-t1 )*B2;
    return C;
}