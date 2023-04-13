resistors = [
    560,
    510,
    180,
    820,
    20,
    22,
    36,
    33,
    120,
    470,
    430,
    750,
    680,
    24,
    39,
    43,
    200,
    750,
    620,
    330,
    390,
    51,
    220,
    270,
    910,
    47,
    470,
    750,
    75,
    100,
    63,
    27,
    30,
]


def find_vals(vwant):
    # add tolerance
    diff = 1000
    vals = []
    vin = [0, 3.3]
    for _, rf in enumerate(resistors):
        for _, r1 in enumerate(resistors):
            for _, r2 in enumerate(resistors):
                vout = [
                    -1 * rf * (vin[1] / r1 - 10 / r2),
                    -1 * rf * (vin[0] / r1 - 10 / r2),
                ]
                d = abs(vwant[0] - vout[0]) + abs(vwant[1] - vout[1])
                if d < diff:
                    diff = d
                    vals = [vout[0], vout[1], rf, r1, r2]
    rf = vals[2]
    r1 = vals[3]
    r2 = vals[4]
    print(
        f"{vin[0]} to {vin[1]}v -> {vals[0]:.2f} to {vals[1]:.2f}v\trf={rf}, r1={r1}, r2={r2}"
    )


find_vals([-10, 10])
find_vals([-5, 5])
find_vals([0, 5])
find_vals([0, 10])
