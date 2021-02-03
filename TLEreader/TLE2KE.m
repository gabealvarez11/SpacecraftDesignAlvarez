% Returns vector of orbital elements [a e i raan arg_periapsis nu]' [deg]
% given ["line 1"; "line 2"; "line 3"] in TLE format.
function oe = tle2oe(input_tle)
    oe = zeros(6,1);
    line_2 = char(input_tle(3));

    mean_motion = 2 * pi / 86400 * str2double(line_2(53:63)); % [rad/s]
    mu_E = 398600.4418; % [km^3/s^2]
    oe(1) = (mu_E/mean_motion^2)^(1/3); % a

    e_string = "0." + string(line_2(27:33));
    oe(2) = str2double(e_string); % e

    oe(3) = str2double(line_2(9:16)); % i

    oe(4) = str2double(line_2(18:25)); % raan

    oe(5) = str2double(line_2(35:42)); % arg_periapsis

    oe(6) = str2double(line_2(44:51)); % nu
end
