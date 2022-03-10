ld deg_to_rad(ld deg) { return deg/180*PI; }
ld rad_to_deg(ld rad) { return rad/PI*180; }
// multiply to rotate about origin. shift + unshift to rotate about pivot
pt rotate_ccw(ld rad) { return polar(1.L,rad); }

