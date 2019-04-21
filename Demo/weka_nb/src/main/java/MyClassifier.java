import weka.classifiers.Classifier;
import weka.core.*;

import java.util.*;
import org.apache.log4j.Logger;

public class MyClassifier {
    final static Logger logger = Logger.getLogger(MyClassifier.class);

    private String[]   inputText       = null;
    private String[]   inputClasses    = null;
    private String     classString     = null;

    private Attribute  classAttribute  = null;
    private Attribute  textAttribute   = null;
    private ArrayList<Attribute> attributeInfo   = null;
    private Instances instances       = null;
    private Classifier classifier      = null;
    private Instances  filteredData    = null;
    private Set modelWords      = null;

    private String     delimitersStringToWordVector = "\\s.,:'\\\"()?!";

    static Hashtable<String, Integer> stringToVec(String text) {
        StringTokenizer tokenizer = new StringTokenizer(text);
        Hashtable<String, Integer> textVec = new Hashtable<>();
        while (tokenizer.hasMoreTokens()) {
            String tk = tokenizer.nextToken();
            if (textVec.containsKey(tk)) {
                textVec.replace(tk, textVec.get(tk) + 1);
            } else {
                textVec.put(tk, 1);
            }
        }
        return textVec;
    }

    public static void main(String args[]) throws Exception {
        String[] classes = {"weka.classifiers.bayes.NaiveBayesMultinomial", "weka.classifiers.bayes.NaiveBayes"};
        String thisClassString;
        if (args.length > 0) {
            thisClassString = args[0];
        } else {
            thisClassString = classes[0];
        }
        logger.info("Using " + thisClassString);

        String[] inputText = {"Chinese Beijing Chinese", "Chinese Chinese Shanghai", "Chinese Macao", "Tokyo Japan Chinese"};
        String[] inputClasses = {"yes", "yes", "yes", "no"};
        String[] testText = {"Chinese Tokyo Japan", "Chinese Chinese Beijing Tokyo", "Chinese Chinese Tokyo"};

        if (inputText.length != inputClasses.length) {
            logger.error("The length of text and classes must be the same!");
            System.exit(1);
        }

        HashSet<String> classSet = new HashSet<>(Arrays.asList(inputClasses));

        HashSet<String> vocabulary = new HashSet<>();
        ArrayList<Hashtable<String, Integer>> inputTextVec = new ArrayList<>();
        for (String text: inputText) {
            StringTokenizer tokenizer = new StringTokenizer(text);
            Hashtable<String, Integer> textVec = stringToVec(text);
            inputTextVec.add(textVec);
            for (String word: textVec.keySet()) {
                vocabulary.add(word);
            }
        }

        ArrayList<Attribute> attInfo = new ArrayList<>();
        for (String word: vocabulary) {
            Attribute att = new Attribute(word);
            attInfo.add(att);
        }

        attInfo.add(new Attribute("class", new ArrayList<>(classSet)));
        Instances dataSet = new Instances("Training set", attInfo, 1000);
        dataSet.setClassIndex(attInfo.size() - 1);
        for (int i = 0; i < inputTextVec.size(); ++i) {
            Instance ist = new DenseInstance(attInfo.size());
            ist.setDataset(dataSet);
            Hashtable<String, Integer> textVec = inputTextVec.get(i);
            for (int j = 0; j < attInfo.size() - 1; ++j) {
                Attribute att = attInfo.get(j);
                String word = att.name();
                ist.setValue(att, textVec.getOrDefault(word, 0));
            }
            ist.setClassValue(inputClasses[i]);
            dataSet.add(ist);
        }

        logger.info("DATA SET: \n" + dataSet);
        Classifier classifier = (Classifier)Utils.forName(Classifier.class, "weka.classifiers.bayes.NaiveBayesMultinomial", null);
        classifier.buildClassifier(dataSet);
        logger.info("classifier info: \n" + classifier.toString());


        for (String text: testText) {
            Hashtable<String, Integer> textVec = stringToVec(text);
            Instance ist = new DenseInstance(attInfo.size());
            ist.setDataset(dataSet);
            for (int j = 0; j < attInfo.size() - 1; ++j) {
                Attribute att = attInfo.get(j);
                String word = att.name();
                ist.setValue(att, textVec.getOrDefault(word, 0));
            }
            double predicted = classifier.classifyInstance(ist);
            Attribute classAtt = attInfo.get(attInfo.size() - 1);
            logger.info(text + " " + ist + " " + classAtt.value((int)predicted) + " (" + predicted + ")");
        }
    }
}