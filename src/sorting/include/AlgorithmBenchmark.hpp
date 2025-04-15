//
// Created by lukasz on 18.03.25.
//

#ifndef AIZO_1_FILEWRITER_HPP
#define AIZO_1_FILEWRITER_HPP

namespace Sorting {
    class
    AlgorithmBenchmark {
    public:
        virtual double run() = 0;
        virtual std::string getConfig() = 0;
        virtual ~AlgorithmBenchmark() = default;
    };
}

#endif //AIZO_1_FILEWRITER_HPP
