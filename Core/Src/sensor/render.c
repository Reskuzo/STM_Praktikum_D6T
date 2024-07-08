/*
 * render.c
 *
 *  Created on: Jul 8, 2024
 *      Author: yannick
 */


// perform linear uint16_terpolation between two colors
// source stackoverflow (with own adjustments, so no GPL License  needed)
uint16_t pick_gradient_color(uint16_t color1, uint16_t color2, float temperature_gradient) {

	/// convert rgb uint16_to rgb565:
	/// as in rgb the always 2 digit are one color #rrggbb,
	// but here the second and third bit overlapp from r-g and g-b
	uint16_t r1 = (color1 >> 11) & 0x1F;
    uint16_t g1 = (color1 >> 5) & 0x3F;
    uint16_t b1 = color1 & 0x1F;

    uint16_t r2 = (color2 >> 11) & 0x1F;
    uint16_t g2 = (color2 >> 5) & 0x3F;
    uint16_t b2 = color2 & 0x1F;

    /// apply ratios between the two colors by using the temperature gradient
    uint16_t r = (uint16_t)(r1 + temperature_gradient * (r2 - r1));
    uint16_t g = (uint16_t)(g1 + temperature_gradient * (g2 - g1));
    uint16_t b = (uint16_t)(b1 + temperature_gradient * (b2 - b1));

    return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
}

/// convert the temperature values of the sensor [-10,70] to a color in the spectrum
///[-10,22]-> [blue, white],
///[ 22,36]-> [white, orange], (high change in color as its the mainly used area)
///[ 36,70]-> [orange, red]
uint16_t convert_temp_to_color(float temp) {
	// the sensor can operate with temperatures in [-10, 70]

    if (temp <= -10)
        return DARK_BLUE;

    if (temp >= 70)
    	return DARK_RED;

    if (temp < 22) {
    	// map temperature from ]-10, 22[ to [0, 1] for the blue to white gradient
    	float temp_gradient = (temp + 10.f) / 32.0f;
    	return pick_gradient_color(DARK_BLUE, WHITE, temp_gradient);
    }

    if (temp < 36) {
        	// map temperature from [-22, 36[ to [0, 1] for the blue to white gradient
        	float temp_gradient = (temp - 22.f) / 14.0f;
        	return pick_gradient_color(WHITE, ORANGE, temp_gradient);
        }


    // map temperature from [36, 70] to [0, 1] for the orange to red gradient
    float temp_gradient = (temp - 36.f) / 34.0f;
    return pick_gradient_color(ORANGE, DARK_RED, temp_gradient);

}
