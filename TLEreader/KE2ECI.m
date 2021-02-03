% Takes input as [a e i raan arg_periapsis nu]. 
% All angles in degrees and a in km.
function func = OE2ECI(input)
    mu_earth = 3.986e5; % km^3/s^2

    a = input(1);
    e = input(2);
    i = input(3);
    raan = input(4);
    arg_periapsis = input(5);
    nu = input(6);

    % Semi-latus rectum.
    p = a * (1 - e^2);

    % Distance from center of the Earth.
    r = p / (1 + e * cosd(nu));

    % Construct the position vector in the PQW frame.
    r_P = r * cosd(nu);
    r_Q = r * sind(nu);
    r_W = 0;

    r_PQW = [r_P; r_Q; r_W];

    % Find the speed.
    specific_energy = - mu_earth / (2 * a);
    v = sqrt(2 * (specific_energy + mu_earth / r));

    % Construct the velocity vector in the PQW frame.
    h = sqrt(mu_earth * p);
    h_PQW = [0; 0; h];

    theta = asind(h / (r * v));

    v_PQW = (r * v * cosd(theta) * r_PQW + cross(h_PQW, r_PQW)) / r ^ 2;

    if i == 0
        if e == 0 % Equatorial and circular orbit: raan, arg_periapsis undefined.
            PQW_R_ECI = eye(3);
        else % Equatorial but non-circular:
            PQW_R_ECI = rotz(-arg_periapsis);
        end
    elseif e == 0 % Circular but non-equatorial orbit: arg_periapsis undefined.
        PQW_R_ECI = rotz(-raan)* rotx(-i);
    else % Non-circular, non-equatorial: all oe defined.
        PQW_R_ECI = rotz(-raan) * rotx(-i) * rotz(-arg_periapsis);
    end

    r_ECI = PQW_R_ECI * r_PQW;
    v_ECI = PQW_R_ECI * v_PQW;

    func = [r_ECI v_ECI];
end
