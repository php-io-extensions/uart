<?php

namespace Zephir\Optimizers\FunctionCall;

use Zephir\Call;
use Zephir\CompilationContext;
use Zephir\CompiledExpression;
use Zephir\Exception\CompilerException;
use Zephir\Optimizers\OptimizerAbstract;

class UartGetAttributesOptimizer extends OptimizerAbstract
{
    public function optimize(array $expression, Call $call, CompilationContext $context)
    {
        if (!isset($expression['parameters']) || count($expression['parameters']) !== 1) {
            throw new CompilerException("'uart_get_attributes' requires exactly one parameter", $expression);
        }

        [$symbolVariable, $resolvedParams, $symbol] = $this->processStringOptimizer(
            $call,
            $context,
            $expression
        );

        $context->headersManager->add('api/uart-config');

        $context->codePrinter->output(
            'uart_get_attributes(' . $symbol . ', ' . $resolvedParams[0] . ');'
        );

        return new CompiledExpression('variable', $symbolVariable->getRealName(), $expression);
    }
}
