require "warp"

function warp(x, y)
    return partialAnnulus(x, y)
end

function mu(x, y)
    return 1.0
end

function lam(x, y)
    return 2.0
end

function force(x, y)
    return 5.0*math.pi^2*math.cos(math.pi*x)*math.cos(math.pi*y),
          -3.0*math.pi^2*math.sin(math.pi*x)*math.sin(math.pi*y)
end

function solution(x, y)
    return math.cos(math.pi * x) * math.cos(math.pi * y), 0
end

function solution_jacobian(x, y)
    return -math.pi * math.sin(math.pi * x) * math.cos(math.pi * y),
           -math.pi * math.cos(math.pi * x) * math.sin(math.pi * y),
            0, 0
end

