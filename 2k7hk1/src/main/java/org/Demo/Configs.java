package org.Demo;

import org.apache.commons.configuration2.Configuration;
import org.apache.commons.configuration2.builder.fluent.Configurations;
import org.apache.commons.configuration2.ex.ConfigurationException;

import java.io.File;

public class Configs {
    private static Configuration config = null;
    public static Configuration getInstance() {
        if (config == null) {
            Configurations cc = new Configurations();
            try {
                config = cc.properties(new File("./conf/searcher.conf"));
            } catch (ConfigurationException e) {
                e.printStackTrace();
            }
        }
        return config;
    }
}
