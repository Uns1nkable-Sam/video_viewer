var Environment = require("qbs.Environment");

function getEnvDefault(env_name, default_value){
    env_value = Environment.getEnv(env_name);
    if (env_value === "") {
        return default_value;
    }
    return env_value;
}
