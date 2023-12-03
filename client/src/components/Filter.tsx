import { useEffect, useState } from "react";
import { GiBroom } from "react-icons/gi";
import { GetMethod } from "@/utils/RestMethods";
import Tooltip from "@/components/Tooltip";
import History, { FILTER } from "@/components/History";
import Checkbox from "@/components/Checkbox";
import Input from "@/components/Input";

export interface Filter {
	filter: string;
	id?: number;
}

const FilterInput = (props: any): JSX.Element => {
	const {
		defaultValue,
		setIgnoreCase,
		updateDefaultValue
	} = props;

	const [selected, setSelected] = useState(false);
	const [filter, setFilter] = useState<Filter[]>([]);

	const updateHistory = (): void => {
		GetMethod("http://localhost:8080/api/v1/Filter", (status: number, response: any) => {
			if (status === 200) setFilter(response.results);
		});
	};

	useEffect(() => {
		updateHistory();
	}, [selected]);

	const renderHistory = (): JSX.Element => {
		if (!filter?.length) return <div></div>;

		return (
			<History
				items={filter}
				endpoint={FILTER}
				updateDefaultValue={updateDefaultValue}
			/>
		);
	};

	const info = 'Este campo contém as extensões de arquivos aceitas na pesquisa. '
		+ 'Para selecionar múltiplas extensões, utilize ";".';

	return (
		<>
			<h2>
				Filtros / Extensões
				{<Tooltip info={info} />}
			</h2>

			<div className="input-content">
				<Input
					id="filter"
					placeholder="Exemplo: .js; .jsx;"
					defaultValue={defaultValue}
					selected={selected}
					setSelected={setSelected}
					onChange={(e) => {
						updateDefaultValue({
							filter: e.target.value
						});
					}}
				/>
				
				<button className="input-buttons" onClick={() => updateDefaultValue({ filter: "" })}>
					<GiBroom />
				</button>

				<Checkbox id="ignoreCase" label="Considerar capitalização" onClick={setIgnoreCase} />
			</div>

			{selected && renderHistory()}
		</>
	);
};

export default FilterInput;