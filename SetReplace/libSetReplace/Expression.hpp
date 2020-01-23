#ifndef Expression_hpp
#define Expression_hpp

#include <functional>
#include <memory>
#include <vector>
#include <unordered_set>

#include "IDTypes.hpp"

namespace SetReplace {
    /** @brief List of atoms without references to events, as can be used in, i.e., rule specification.
     */
    using AtomsVector = std::vector<Atom>;
    
    /** @brief Expression, as a part of the set, i.e., (hyper)edges in the graph.
     */
    struct SetExpression {
        /** @brief Derived from the input expressions that produced this one as an output. Used to name subsequent atoms / vertices.
         */
        ExpressionID id;
        
        /** @brief Ordered list of atoms the expression contains.
         */
        AtomsVector atoms;
        
        /** @brief Substitution event that has this expression as part of its output.
         */
        EventIndex creatorEvent;
        
        /** @brief Substitution event that has this expression as part of its input.
         */
        EventIndex destroyerEvent = finalStateEvent;
        
        /** @brief Layer of the causal network this expression belongs to.
         */
        Generation generation;
    };
    
    /** @brief AtomsIndex keeps references to set expressions accessible by atoms, which is useful for matching.
     */
    class AtomsIndex {
    public:
        /** @brief Creates an empty index.
         * @param getAtomsVector datasource function that returns the list of atoms for a requested expression.
         */
        AtomsIndex(const std::function<AtomsVector(ExpressionIndex)>& getAtomsVector);
        
        /** @brief Removes expressions with specified indices from the index.
         */
        void removeExpressions(const std::vector<ExpressionIndex>& expressionIndices);
        
        /** @brief Adds expressions with specified indices to the index.
         */
        void addExpressions(const std::vector<ExpressionIndex>& expressionIndices);
        
        /** @brief Returns the list of expressions containing a specified atom.
         */
        const std::unordered_set<ExpressionIndex> expressionsContainingAtom(const Atom atom) const;
        
    private:
        class Implementation;
        std::shared_ptr<Implementation> implementation_;
    };
}

#endif /* Expression_hpp */
